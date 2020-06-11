/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:31:50 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/11 15:35:20 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "stdio.h"

void	orphaned_jobs(void)
{
	t_job *job;

	job = g_job_head;
	while (job)
	{
		if (!job_is_completed(job) && job_is_stopped(job))
		{
			kill(-(job->pgid), SIGCONT);
			kill(-(job->pgid), SIGHUP);
		}
		else if (!job_is_completed(job))
		{
			kill(-(job->pgid), SIGHUP);
		}
		job = job->next;
	}
}

char	*get_job_status(t_job *job)
{
	if (job_is_completed(job))
		return ("Done");
	else if (job_is_stopped(job))
		return ("Stopped");
	else
		return ("Running");
}

void	print_job_info(t_job *job, char *arg, int last[2])
{
	char c;

	c = ' ';
	if (last[0] == job->number)
		c = '+';
	if (last[0] && last[1] == job->number)
		c = '-';
	if (job->pgid == 0)
		ft_printf("jobs: no such jobs\n");
	else if (arg == NULL)
		ft_printf("[%d]%c\t %s \t\t %s\n", job->number, c,
					get_job_status(job), job->line);
	else if (ft_strcmp(arg, "-l") == 0)
		ft_printf("[%d]%c\t %d %s \t\t %s\n", job->number, c, job->pgid,
					get_job_status(job), job->line);
	else if (ft_strcmp(arg, "-p") == 0)
		ft_printf("%d\n", job->pgid);
}

void	get_last_process(int *last0, int *last1)
{
	t_jobnb *jobnb;
	t_job	*tmp;

	tmp = NULL;
	jobnb = g_jobnb;
	while (jobnb && jobnb->next)
		jobnb = jobnb->next;
	while (jobnb && (tmp = find_job_by_number(jobnb->number))
		&& tmp->pgid <= 0 && jobnb->prev)
		jobnb = jobnb->prev;
	if (!tmp || tmp->pgid == 0)
		*last0 = 0;
	else
	{
		*last0 = jobnb->number;
		jobnb = jobnb->prev;
		if (jobnb && find_job_by_number(jobnb->number)->pgid != 0)
			*last1 = jobnb->number;
		else
			*last1 = 0;
	}
}

int		ft_jobs(char **argv, char ***tenv)
{
	t_job		*job;
	int			last_jobs[2];

	(void)tenv;
	job = g_job_head;
	update_status();
	get_last_process(&last_jobs[0], &last_jobs[1]);
	if (argv[1] && argv[1][0] != '-'
		&& (job = find_job_by_number(ft_atoi(argv[1]))))
		print_job_info(job, NULL, last_jobs);
	else if (argv[1] && argv[2] && argv[2][0] != '-'
		&& (job = find_job_by_number(ft_atoi(argv[2]))))
		print_job_info(job, argv[1], last_jobs);
	else if (job == NULL)
		ft_printf("jobs: no such jobs\n");
	else
	{
		while (job && job->pgid != 0)
		{
			print_job_info(job, argv[1], last_jobs);
			job = job->next;
		}
	}
	return (0);
}
