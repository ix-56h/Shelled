/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:45:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/05/11 15:23:47 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "stdio.h"
#include <sys/wait.h>

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
		if (WIFEXITED(status))
			add_set("?", ft_itoa(WEXITSTATUS(status)));
		while (!mark_process_status (pid, status) && shall_we_wait())
		{
			pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
			if (WIFEXITED(status))
				add_set("?", ft_itoa(WEXITSTATUS(status)));
		}
	}
}

void
format_job_info (t_job *j, const char *status)
{
	ft_printf("\n[%d]+\t %s \t %s\n", j->number, status, j->line);
}

void do_job_notification (void)
{
	t_job *j;
	t_job *jnext;

	update_status();
	j = g_job_head;
	while(j)
		{
			jnext = j->next;
			if (job_is_completed (j)) {
				if (WIFSIGNALED(j->list->status))
					format_job_info (j, "terminated");
				else
					format_job_info (j, "completed");
				j->is_notified = 1;
			}
			else if (job_is_stopped (j) && !j->is_notified) {
				format_job_info (j, "stopped");
				push_back(j->number);
				j->is_notified = 1;
			}
			add_set("!", ft_itoa(j->pgid));
			j = jnext;
		}
}
