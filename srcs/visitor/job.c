/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:26:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/23 14:48:57 by mguerrea         ###   ########.fr       */
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

int			mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		j = g_job_head;
		while (j)
		{
			p = j->list;
			while (p)
			{
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
					{
						p->is_stopped = 1;
						j->is_notified = 0;
					}
					else
					{
						p->is_finish = 1;
						p->ret = status;
					}
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
		ft_dprintf(3, "No child process %d.\n", pid);
		return (-1);
	}
	else if (pid == 0)
		return (-1);
	else
	{
		ft_dprintf(3, "waitpid err\n");
		return (-1);
	}
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

void		wait_for_job(t_job *job)
{
	int		status;
	char	*exit_status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		exit_status = ft_itoa(WEXITSTATUS(status));
		add_set("?", exit_status);
		free(exit_status);
	}
	while (!mark_process_status(pid, status) && !job_is_stopped(job) && !job_is_completed(job))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			exit_status = ft_itoa(WEXITSTATUS(status));
			add_set("?", exit_status);
			free(exit_status);
		}
	}
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
