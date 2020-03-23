/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:10:01 by mguerrea          #+#    #+#             */
/*   Updated: 2020/03/23 15:41:28 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "builtins.h"

t_job *find_job_fg(t_job *job)
{
	while (job && job->next)
		job = job->next;
	while (job && job->prev && job->pgid == 0)
		job = job->prev;
	if (job->pgid == 0)
		return(NULL);
	return (job);
}

int ft_fg(char **argv, char ***tenv)
{
	t_job *job;
	int number;

	(void)tenv;
	job = g_job_head;
	if (argv[1] == NULL) // find last job
		job = find_job_fg(job);
	else
		job = find_job_by_number(ft_atoi(argv[1]));
	if (!job)
		ft_putendl_fd("fg: no such job", 2);
	else if (job_is_stopped(job))
	{
		ft_printf("%s\n", job->line);
		put_job_in_foreground(job, 1);
	}
	else
	{
		ft_printf("%s\n", job->line);
		put_job_in_foreground(job, 0);
	}
	return (0);
}