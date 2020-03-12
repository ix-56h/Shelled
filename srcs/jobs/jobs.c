/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:31:50 by mguerrea          #+#    #+#             */
/*   Updated: 2020/03/12 15:58:12 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"

void update_status (void)
{
	int status;
	pid_t pid;

	do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status));
}

void
format_job_info (t_job *j, const char *status)
{
	fprintf (2, "%ld (%s): %s\n", (long)j->pgid, status, "j->command");
}

void do_job_notification (void)
{
	t_job *j, *jlast, *jnext;
	t_process *p;

	/* Update status information for child processes.  */
	update_status ();

	jlast = NULL;
	for (j = g_job_head; j; j = jnext)
		{
			jnext = j->next;

			/* If all processes have completed, tell the user the job has
				 completed and delete it from the list of active jobs.  */
			if (job_is_completed (j)) {
				format_job_info (j, "completed");
				if (jlast)
					jlast->next = jnext;
				else
					g_job_head = jnext;
		//    free_job (j);
			}

			/* Notify the user about stopped jobs,
				 marking them so that we won’t do this more than once.  */
			else if (job_is_stopped (j) && !j->is_notified) {
				format_job_info (j, "stopped");
				j->is_notified = 1;
				jlast = j;
			}

			/* Don’t say anything about jobs that are still running.  */
			else
				jlast = j;
		}
}

int ft_jobs(char **argv, char ***tenv)
{
	t_job *job;
	t_process *process;
	int i;

	job = g_job_head;
	while (job)
	{
	//	if (job->pgid != 0)
	//	{
		ft_putnbr(job->number);
		ft_putstr("\t");
		ft_putnbr(job->pgid);
		ft_putstr("\t");
		process = job->list;
		while (process)
		{
			i = -1;
			while(process->command[++i])
			{
				ft_putstr(process->command[i]);
				ft_putstr(" ");
			}
			process = process->next;
		}
		
		if (job_is_completed(job))
			ft_putendl("COMPLETED");
		else if (job_is_stopped(job))
			ft_putendl("STOPPED");
		else
			ft_putendl("RUNNING");
	//	}
		job = job->next;
	}
	return (0);
}