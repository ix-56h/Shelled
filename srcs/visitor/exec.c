/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/08 19:17:46 by mguerrea         ###   ########.fr       */
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


void
launch_process (t_process *p, pid_t pgid,
                int infile, int outfile, int errfile,
                int foreground, t_node *cmd)
{
  pid_t pid;

      pid = getpid ();
      if (pgid == 0) pgid = pid;
      setpgid (pid, pgid);
      if (foreground)
        tcsetpgrp (STDIN_FILENO, pgid);

      signal (SIGINT, SIG_DFL);
      signal (SIGQUIT, SIG_DFL);
      signal (SIGTSTP, SIG_DFL);
      signal (SIGTTIN, SIG_DFL);
      signal (SIGTTOU, SIG_DFL);
      signal (SIGCHLD, SIG_DFL);

  if (infile != STDIN_FILENO)
    {
      dup2 (infile, STDIN_FILENO);
      close (infile);
    }
  if (outfile != STDOUT_FILENO)
    {
      dup2 (outfile, STDOUT_FILENO);
      close (outfile);
    }
  if (errfile != STDERR_FILENO)
    {
      dup2 (errfile, STDERR_FILENO);
      close (errfile);
    }

  execvp(cmd->data, cmd->args);
  perror ("execvp");
  exit (1);
}

void
launch_job (t_job *j, int foreground, t_node *cmd)
{
  t_process *p;
  pid_t pid;
  int mypipe[2], infile, outfile;

  infile = STDIN_FILENO; // j->stdin;
  for (p = j->list; p; p = p->next)
    {
      /* Set up pipes, if necessary.  */
      if (p->next)
        {
          if (pipe (mypipe) < 0)
            {
              perror ("pipe");
              exit (1);
            }
          outfile = mypipe[1];
        }
      else
        outfile = STDOUT_FILENO; // j->stdout;

      /* Fork the child processes.  */
      pid = fork ();
      if (pid == 0)
        /* This is the child process.  */
        launch_process (p, j->pgid, infile,
                        outfile, STDERR_FILENO, foreground, cmd);
      else if (pid < 0)
        {
          /* The fork failed.  */
          perror ("fork");
          exit (1);
        }
      else
        {
          /* This is the parent process.  */
          p->pid = pid;
   //       if (shell_is_interactive)
    //        {
              if (!j->pgid)
                j->pgid = pid;
              setpgid (pid, j->pgid);
    //        }
        }

      /* Clean up after pipes.  */
      if (infile != STDIN_FILENO)//j->stdin)
        close (infile);
      if (outfile != STDOUT_FILENO)//j->stdout)
        close (outfile);
      infile = mypipe[0];
    }

//  format_job_info (j, "launched");

//   if (!shell_is_interactive)
//     wait_for_job (j);
//  else if (foreground)
    put_job_in_foreground (j, 0);
//  else
 //   put_job_in_background (j, 0);
}

int				exec_with_fork(t_node *cmd, char **env, t_io_lists io,
					t_job *job)
{
	pid_t		pid;
	t_process	*process;
	int			return_value;

//	launch_job(job, 1, cmd);

	if ((pid = fork()) == -1)
		return (1);
	else if (pid == 0)
	{
		pid = getpid();
		if (!io.piped || (io.piped && !io.piped->prev))
		{
			setpgid(pid, pid);
			job->pgid = pid;
		}
		else
			setpgid(pid, job->pgid);
	//	tcsetpgrp (STDIN_FILENO, job->pgid);
		set_pipe_fd(io.piped);
		close_unused_pipe_fd(io.piped);
		close_all_pipe(io);
		set_redir_fd(io.redir);
		if (lookforbuiltin(cmd->data))
		{
			return_value = lookforbuiltin(cmd->data)(cmd->args,
			((env) ? &env : &g_env));
			exit(return_value);
		}
		signal (SIGINT, SIG_DFL);
      	signal (SIGQUIT, SIG_DFL);
      	signal (SIGTSTP, SIG_DFL);
      	signal (SIGTTIN, SIG_DFL);
      	signal (SIGTTOU, SIG_DFL);
      	signal (SIGCHLD, SIG_DFL);
		execve(cmd->data, cmd->args, ((env) ? env : g_env));
		exit(1);
	}
	else
	{
		close_used_pipe_fd(io.piped);
		process = find_process_by_pid(job->list, UNUSED_JOB);
		process->pid = pid;
		//Ca decone ici
		if (!io.piped || (io.piped && !io.piped->prev))
		{
			setpgid(pid, pid);
			job->pgid = pid;
		}
		else
			setpgid(pid, job->pgid);
		//et ca fini la
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
