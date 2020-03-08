/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/08 20:29:32 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "sh.h"
#include "builtins.h"
#include "exec.h"

pid_t shell_pgid;
void wait_for_job (t_job *j);

void put_job_in_foreground (t_job *j, int cont)
{
  /* Put the job into the foreground.  */
  tcsetpgrp (0, j->pgid);


  /* Send the job a continue signal, if necessary.  */
  if (cont)
    {
      restore_term(1);
      if (kill (- j->pgid, SIGCONT) < 0)
        perror ("kill (SIGCONT)");
    }


  /* Wait for it to report.  */
  wait_for_job (j);

  /* Put the shell back in the foreground.  */
  tcsetpgrp (0, shell_pgid);

  /* Restore the shell’s terminal modes.  */
  restore_term(2);
}

int				exec_with_fork(t_node *cmd, char **env, t_io_lists io,
					t_job *job)
{
	pid_t		pid;
	t_process	*process;
	int			return_value;

	if ((pid = fork()) == -1)
		return (1);
	else if (pid == 0)
	{
		pid = getpid();
		if (!io.piped || (io.piped && !io.piped->prev && io.piped->used == 0))
		{
			setpgid(pid, pid);
			job->pgid = pid;
		}
		else
			setpgid(pid, job->pgid);
		dprintf(2, "pgid = %d\n", job->pgid);
		tcsetpgrp (STDIN_FILENO, job->pgid);
		set_pipe_fd(io.piped);
		close_unused_pipe_fd(io.piped);
		close_all_pipe(io);
		set_redir_fd(io.redir);
		signal (SIGINT, SIG_DFL);
      	signal (SIGQUIT, SIG_DFL);
      	signal (SIGTSTP, SIG_DFL);
      	signal (SIGTTIN, SIG_DFL);
      	signal (SIGTTOU, SIG_DFL);
      	signal (SIGCHLD, SIG_DFL);
		if (lookforbuiltin(cmd->data))
		{
			return_value = lookforbuiltin(cmd->data)(cmd->args,
			((env) ? &env : &g_env));
			exit(return_value);
		}
		execve(cmd->data, cmd->args, ((env) ? env : g_env));
		exit(1);
	}
	else
	{
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
	process = find_process_by_pid(job->list, UNUSED_JOB);
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
		process = find_process_by_pid(job->list, UNUSED_JOB);
		process->pid = pid;
		return (0);
	}
}

int				builtin_controler(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	int		err;

	if (io.piped)
		err = exec_with_fork(cmd, env, io, job);
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
			find_process_by_pid(job->list, UNUSED_JOB)->pid = ERR_JOB;
	}
	return (err);
}
