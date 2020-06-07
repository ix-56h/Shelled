/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:45:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/06 17:20:03 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "stdio.h"
#include "builtins.h"
#include <sys/wait.h>

int		shall_we_wait(void)
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

void	update_status(void)
{
	int		status;
	pid_t	pid;

	if (shall_we_wait())
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (WIFEXITED(status))
			set_ret_value("?", ft_itoa(WEXITSTATUS(status)));
		while (!mark_process_status(pid, status) && shall_we_wait())
		{
			pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
			if (WIFEXITED(status))
				set_ret_value("?", ft_itoa(WEXITSTATUS(status)));
		}
	}
}

void	format_job_info(t_job *j, const char *status)
{
	ft_printf("[%d]+\t %s \t %s\n", j->number, status, j->line);
}

void	do_job_notification(void)
{
	t_job *j;

	update_status();
	j = g_job_head;
	while (j)
	{
		if (job_is_completed(j))
		{
			if (WIFSIGNALED(j->list->status))
				format_job_info(j, "Terminated");
			else
				format_job_info(j, "Completed");
			j->is_notified = 1;
		}
		else if (job_is_stopped(j) && !j->is_notified)
		{
			format_job_info(j, "Stopped");
			push_back(j->number);
			j->is_notified = 1;
		}
		set_ret_value("!", ft_itoa(j->pgid));
		j = j->next;
	}
	clean_job();
}

void	mark_job_as_running(t_job *j)
{
	t_process *p;

	p = j->list;
	while (p)
	{
		p->is_stopped = 0;
		p = p->next;
	}
	j->is_notified = 0;
}
