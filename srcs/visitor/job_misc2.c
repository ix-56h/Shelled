/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_misc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 02:05:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 02:07:31 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "visitor_misc.h"
#include "sh.h"
#include "ft_printf.h"
#include "ligne.h"
#include "job.h"

void		clean_job(void)
{
	t_job	*head;
	t_job	*nav;
	t_job	*next;

	head = g_job_head;
	nav = head;
	while (nav)
	{
		next = nav->next;
		if (job_is_finish(nav) && nav->is_notified == 1)
		{
			if (head == nav)
			{
				g_job_head = next;
				head = g_job_head;
			}
			del_jobnb(nav->number);
			dl_free_with_data((t_dl_node *)nav->list, free);
			if (nav->line)
				free(nav->line);
			dl_del_one((t_dl_node *)nav);
		}
		nav = next;
	}
}

void		free_all_job(t_job *job)
{
	dl_free_with_data((t_dl_node *)job, dl_free_list);
}

void		put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(0, job->pgid);
	if (cont)
	{
		restore_term(1);
		kill(-job->pgid, SIGCONT);
	}
	wait_for_job(job);
	tcsetpgrp(0, g_shell_pgid);
	restore_term(2);
}

t_job		*create_job(void)
{
	t_job	*last_job;
	t_job	**job;

	job = &g_job_head;
	dl_append_node((t_dl_node **)job, ft_calloc(sizeof(t_job)));
	last_job = (t_job *)dl_get_last((t_dl_node *)*job);
	last_job->number = get_next_job_count();
	last_job->is_notified = 1;
	add_jobnb(last_job->number);
	return (last_job);
}

int			get_next_job_count(void)
{
	int		max;
	t_job	*nav;

	nav = g_job_head;
	max = 1;
	if (!nav)
		return (max);
	while (nav)
	{
		if (nav->number >= max)
			max = nav->number + 1;
		nav = nav->next;
	}
	return (max);
}
