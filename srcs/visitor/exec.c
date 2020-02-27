/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/27 01:06:22 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "builtins.h"
#include "exec.h"



int				exec_with_fork(t_node *cmd, char **env, t_io_lists io,
					t_job *job)
{
	pid_t		pid;
	t_process	*process;

	if ((pid = fork()) == -1)
		return (1);
	else if (pid == 0)
	{
		set_pipe_fd(io.piped);
		close_unused_pipe_fd(io.piped);
		close_all_pipe(io);
		set_redir_fd(io.redir);
		execve(cmd->data, cmd->args, ((env) ? env : g_env));
		exit(1);
	}
	else
	{
		close_used_pipe_fd(io.piped);
		process = find_process_by_pid(job->data, UNUSED_JOB);
		process->pid = pid;
		return (0);
	}
}

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
	process = find_process_by_pid(job->data, UNUSED_JOB);
	process->pid = BUILTIN_JOB;
	process->ret = ret;
	process->is_finish = 1;
	return (0);
}

int				exec_builtin_fork(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	int		pid;
	int		return_value;
	t_process	*process;

	if ((pid = fork()) == -1)
		return (1);
	else if (pid == 0)
	{
		set_pipe_fd(io.piped);
		close_unused_pipe_fd(io.piped);
		close_all_pipe(io);
		set_redir_fd(io.redir);
		return_value = lookforbuiltin(cmd->data)(cmd->args,
			((env) ? &env : &g_env));
		exit(return_value);
	}
	else
	{
		close_used_pipe_fd(io.piped);
		process = find_process_by_pid(job->data, UNUSED_JOB);
		process->pid = pid;
		return (0);
	}
}

int				builtin_controler(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	int		err;
	int		return_value;

	if (io.piped)
		err = exec_builtin_fork(cmd, env, io, job);
	else
		err = exec_builtin_no_fork(cmd, env, io, job);
	return (err);
}

int				exec_cmd(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	int		err;

	err = 0; //separer err et pid
	if (lookforbuiltin(cmd->data))
		err = builtin_controler(cmd, env, io, job);
	else if (is_path(cmd->data))
	{
		if ((err = test_path(cmd)) == 0)
			err = exec_with_fork(cmd, env, io, job);
	}
	else
	{
		if ((err = test_env(cmd, env)) == 0)
			err = exec_with_fork(cmd, env, io, job);
		else
			find_process_by_pid(job->data, UNUSED_JOB)->pid = ERR_JOB;
	}
	return (err);
}
