/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:26:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/02 00:07:47 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "libft.h"
#include "visitor_misc.h"

t_process	*create_process(pid_t pid)
{
	t_process	*new_process;

	if (!(new_process = ft_calloc(sizeof(t_process))))
		return (NULL);
	new_process->pid = pid;
	return	(new_process);
}

t_process	*find_process_by_pid(t_process *process, pid_t pid)
{
	while (process && process->prev)
		process = process->prev;
	while (process)
	{
		if (process->pid == pid)
			return (process);
		process = process->next;
	}
	return (NULL);
}

int			job_is_finish(t_job *job)
{
	t_process *process;

	process = (t_process*)job->data;
	while (process)
	{
		if (process->is_finish == 0 && process->pid != UNUSED_JOB)
			return (0);
		process = process->next;
	}
	return (1);
}

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
		if (job_is_finish(nav) && nav->next && nav->next->next)
		{
			if (head == nav)
			{
				g_job_head = next;
				head = g_job_head;
			}
			dl_free_list(nav->data);
			dl_del_one(nav);
		}
		nav = next;
	}
}