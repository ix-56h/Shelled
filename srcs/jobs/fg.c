/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:10:01 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/16 13:53:00 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "builtins.h"

t_job	*find_job_fg(t_job *job)
{
	t_jobnb	*jobnb;
	t_job	*tmp;

	(void)job;
	jobnb = g_jobnb;
	while (jobnb && jobnb->next)
		jobnb = jobnb->next;
	tmp = find_job_by_number(jobnb->number);
	while (tmp && tmp->pgid == 0 && jobnb->prev)
	{
		jobnb = jobnb->prev;
		tmp = find_job_by_number(jobnb->number);
	}
	if (tmp->pgid == 0)
		return (NULL);
	return (tmp);
}

int		ft_fg(char **argv, char ***tenv)
{
	t_job	*job;

	(void)tenv;
	job = g_job_head;
	if (argv[1] == NULL)
		job = find_job_fg(job);
	else if (argv[1][0] == '%')
		job = find_job_by_number(ft_atoi(argv[1] + 1));
	else
		job = find_job_by_number(ft_atoi(argv[1]));
	if (!job || job->pgid == 0)
		ft_putendl_fd("fg: no such job", 2);
	else
	{
		ft_printf("%s\n", job->line);
		if (job_is_stopped(job))
			continue_job(job, 1);
		else
			put_job_in_foreground(job, 0);
	}
	return (0);
}
