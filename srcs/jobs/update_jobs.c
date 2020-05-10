/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:45:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/05/10 20:30:18 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "stdio.h"

int shall_we_wait(void)
{
	t_job *job;

	job = g_job_head;
	if (job == NULL || job->pgid == 0)
		return (0);
	
	while (job)
	{
		if (!job_is_completed(job) && job->pgid != 0)
			return (1);
		job = job->next;
	}
	return (0);
}

void update_status (void)
{
	int status;
	pid_t pid;

	if (shall_we_wait())
	{
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status) && shall_we_wait())
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	}
}

void
format_job_info (t_job *j, const char *status)
{
	ft_printf("\n[%d]+\t %s \t %s\n", j->number, status, j->line);
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
		   		free_job (j);
			}

			/* Notify the user about stopped jobs,
				 marking them so that we won’t do this more than once.  */
			else if (job_is_stopped (j) && !j->is_notified) {
				format_job_info (j, "stopped");
				push_back(j->number);
				j->is_notified = 1;
				jlast = j;
			}

			/* Don’t say anything about jobs that are still running.  */
			else
				jlast = j;
		}
}