/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:45:12 by mguerrea          #+#    #+#             */
/*   Updated: 2020/03/11 19:51:05 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "builtins.h"

void
put_job_in_background (t_job *job, int cont)
{
  /* Send the job a continue signal, if necessary.  */
  if (cont)
    if (kill (-job->pgid, SIGCONT) < 0)
    	perror ("kill (SIGCONT)");
}

/* Mark a stopped job J as being running again.  */

void
mark_job_as_running (t_job *j)
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


/* Continue the job J.  */

void
continue_job (t_job *j, int foreground)
{
  mark_job_as_running (j);
  if (foreground)
    put_job_in_foreground (j, 1);
  else
    put_job_in_background (j, 1);
}

t_job *find_job_bg(t_job *job)
{
	while (job && job->next)
		job = job->next;
	while (job && job->prev)
	{
		if (!job_is_completed(job) && job_is_stopped(job))
			break;
		job = job->prev;
	}
	return (job);
}

int ft_bg(char **argv, char ***tenv)
{
	t_job *job;
	int number;

	(void)tenv;
	job = g_job_head;
	if (argv[1] == NULL) // find last jobs
	{
		job = find_job_bg(job);
	}
	else
	{
		number = ft_atoi(argv[1]);
		while (job && job->number != number)
			job = job->next;
	}
	if (!job)
		return (ERR_NO_JOB);
	if (job_is_stopped(job))
		continue_job(job, 0);
	else
		return (ERR_ALREADY_BG);
	return (0);
}