/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/08 20:33:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "visitor_misc.h"
#include "ligne.h"
#include "exec.h"
#include "ft_printf.h"

static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}


int
mark_process_status (pid_t pid, int status)
{
  t_job *j;
  t_process *p;

	dprintf(2, "pid = %d\n", pid);
  if (pid > 0)
    {
      /* Update the record for the process.  */
      for (j = g_job_head; j; j = j->next)
        for (p = j->list; p; p = p->next)
          if (p->pid == pid)
            {
              p->status = status;
              if (WIFSTOPPED (status))
                p->is_stopped = 1;
              else
                {
                  p->is_finish = 1;
                  if (WIFSIGNALED (status))
                    fprintf (stderr, "%d: Terminated by signal %d.\n",
                             (int) pid, WTERMSIG (p->status));
                }
              return 0;
             }
      fprintf (stderr, "No child process %d.\n", pid);
      return -1;
    }

  else if (pid == 0)
    /* No processes ready to report.  */
    return -1;
  else {
    /* Other weird errors.  */
    perror ("waitpid");
    return -1;
  }
}


/* Return true if all processes in the job have stopped or completed.  */
int job_is_stopped (t_job *j)
{
  t_process *p;

  for (p = j->list; p; p = p->next)
    if (!p->is_finish && !p->is_stopped)
      return 0;
//	dprintf(2, "stopped\n");
  return 1;
}

int job_is_completed (t_job *j)
{
  t_process *p;

  for (p = j->list; p; p = p->next)
    if (!p->is_finish)
      return 0;
  return 1;
}



void wait_for_job (t_job *j)
{
  int status;
  pid_t pid;

  do
    pid = waitpid (WAIT_ANY, &status, WUNTRACED);
  while (!mark_process_status (pid, status) // wait until every process is completed or stopped
         && !job_is_stopped (j)	
         && !job_is_completed (j));
}

void put_job_in_foreground (t_job *j, int cont);
pid_t shell_pgid;

void			wait_and_ret(t_io_lists io, t_job *job)
{
	int			ret_value;
	int			ret_pid;
	t_process	*tmp_process;
	int status;

	if ((io.piped && !io.piped->next && io.piped->used == 1) || !io.piped)
	{
		// if this is the last process, put the whole job in foreground and wait for it
		// we need to check if this is a builtin or not
		put_job_in_foreground(job, 0); 
	}
}

int	exec_command(t_node *node, t_io_lists *io, t_job **job)
{
	int	ctrlc;
	int	err;

	ctrlc = 0;
	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	dl_append_node((t_dl_node **)&(*job)->list, (t_dl_node *)create_process(UNUSED_JOB));
	err = exec_cmd(node, NULL, *io, *job);
	wait_and_ret(*io, *job);
	set_used_fd(io->piped);
	restore_term(2);
	signal(SIGINT, SIG_DFL);
	return (err);	
}