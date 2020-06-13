/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 01:55:09 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 02:05:12 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "sh.h"
#include "ft_printf.h"
#include "ligne.h"
#include "job.h"

t_process	*create_process(pid_t pid)
{
	t_process	*new_process;

	if (!(new_process = ft_calloc(sizeof(t_process))))
		return (NULL);
	new_process->pid = pid;
	return (new_process);
}

t_process	*find_process_by_pid(t_process *process, pid_t pid)
{
	if (g_exp_error)
		free(process->command);
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

	process = (t_process*)job->list;
	while (process)
	{
		if (process->is_finish == 0 && process->pid != UNUSED_JOB)
			return (0);
		process = process->next;
	}
	return (1);
}

int			job_is_stopped(t_job *j)
{
	t_process *p;

	p = j->list;
	while (p)
	{
		if (!p->is_finish && !p->is_stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int			job_is_completed(t_job *j)
{
	t_process		*p;

	p = j->list;
	while (p)
	{
		if (!p->is_finish)
			return (0);
		p = p->next;
	}
	return (1);
}
