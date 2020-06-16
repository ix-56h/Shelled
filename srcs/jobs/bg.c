/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:45:12 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/16 13:54:57 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "builtins.h"

void	put_job_in_background(t_job *job, int cont)
{
	job->is_notified = 0;
	if (cont)
	{
		kill(-job->pgid, SIGCONT);
	}
}

void	continue_job(t_job *j, int foreground)
{
	mark_job_as_running(j);
	push_front(j->number);
	if (foreground)
		put_job_in_foreground(j, 1);
	else
		put_job_in_background(j, 1);
}

t_job	*find_job_bg(void)
{
	t_jobnb	*jobnb;
	t_job	*tmp;

	jobnb = g_jobnb;
	while (jobnb && jobnb->next)
		jobnb = jobnb->next;
	tmp = (jobnb) ? find_job_by_number(jobnb->number) : NULL;
	while (jobnb && jobnb->prev)
	{
		if (!job_is_completed(tmp) && job_is_stopped(tmp) && tmp->pgid != 0)
			break ;
		jobnb = jobnb->prev;
		tmp = find_job_by_number(jobnb->number);
	}
	return (tmp);
}

t_job	*find_job_by_number(int nb)
{
	t_job	*job;

	job = g_job_head;
	while (job && job->number != nb)
		job = job->next;
	return (job);
}

int		ft_bg(char **argv, char ***tenv)
{
	t_job	*job;

	(void)tenv;
	job = g_job_head;
	if (argv[1] == NULL)
		job = find_job_bg();
	else if (argv[1][0] == '%')
		job = find_job_by_number(ft_atoi(argv[1] + 1));
	else
		job = find_job_by_number(ft_atoi(argv[1]));
	if (!job || !job->pgid)
		ft_putendl_fd("bg: no such job", 2);
	else if (job_is_stopped(job))
	{
		continue_job(job, 0);
		ft_printf("[%d] %s\n", job->number, job->line);
	}
	else
		ft_putendl_fd("bg: job already in background", 2);
	return (0);
}
