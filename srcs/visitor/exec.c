/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/13 01:46:47 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "sh.h"
#include "builtins.h"
#include "exec.h"
#include <sys/wait.h>

int				exec_builtin_no_fork(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	t_builtin	exec_builtin;
	int			ret;
	t_process	*process;

	save_and_restore_fd(0);
	set_pipe_fd(io.piped);
	set_redir_fd(io.redir);
	exec_builtin = lookforbuiltin(cmd->data);
	ret = exec_builtin(cmd->args, ((env) ? &env : &g_env));
	close_used_pipe_fd(io.piped);
	save_and_restore_fd(1);
	process = find_process_by_pid(job->list, UNUSED_JOB);
	process->pid = BUILTIN_JOB;
	process->ret = ret;
	process->is_finish = 1;
	return (0);
}

void			child_exec(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	pid_t	pid;
	int		ret;

	pid = getpid();
	if (!io.piped || (io.piped && !io.piped->prev && io.piped->used == 0))
	{
		setpgid(pid, pid);
		job->pgid = pid;
	}
	else
		setpgid(pid, job->pgid);
	signal (SIGINT, SIG_DFL);
    signal (SIGQUIT, SIG_DFL);
    signal (SIGTSTP, SIG_DFL);
    signal (SIGTTIN, SIG_DFL);
    signal (SIGTTOU, SIG_DFL);
    signal (SIGCHLD, SIG_DFL);
	if (lookforbuiltin(cmd->data))
	{
		ret = lookforbuiltin(cmd->data)(cmd->args,
		((env) ? &env : &g_env));
		exit(ret);
	}
	execve(cmd->data, cmd->args, ((env) ? env : g_env));
	exit(1);
}

void			after_fork_routine(pid_t pid, t_io_lists io, t_job *job)
{
	t_process	*process;

	close_used_pipe_fd(io.piped);
	process = find_process_by_pid(job->list, UNUSED_JOB);
	process->pid = pid;
	if (!io.piped || (io.piped && !io.piped->prev && io.piped->used == 0))
	{
		setpgid(pid, pid);
		job->pgid = pid;
	}
	else
		setpgid(pid, job->pgid);
}

void			apply_fd(t_io_lists io)
{
	set_pipe_fd(io.piped);
	close_all_pipe(io);
	set_redir_fd(io.redir);
}

int				exec_cmd(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	pid_t		pid;
	t_process	*process;
	int		ret;

	ret = 0;
	if (!io.piped && !io.redir && !io.background && lookforbuiltin(cmd->data))
			ret = exec_builtin_no_fork(cmd, env, io, job);
	else
	{
		if ((pid = fork()) == -1)
			return (-1);
		else if (pid == 0)
		{
			apply_fd(io);
			if (lookforbuiltin(cmd->data))
				child_exec(cmd, env, io, job);
			else if (is_path(cmd->data))
			{
				if ((ret = test_path(cmd)) == 0)
					child_exec(cmd, env, io, job);
				else
					exit(130);
			}
			else
			{
				if ((ret = test_env(cmd, env)) == 0)
					child_exec(cmd, env, io, job);
				else
					exit(130);
			}
		}
		after_fork_routine(pid, io, job);
	}
	return (ret);
}