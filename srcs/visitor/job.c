/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:26:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/13 01:05:34 by akeiflin         ###   ########.fr       */
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
	if (job_is_completed(job))
		return (1);
	return (0);
}

void		free_process(t_process *process)
{
	if (process)
	{
		if (process->prev)
			process->prev->next = process->next;
		if (process->next)
			process->next->prev = process->prev;
		if (process->command)
			free_env(process->command);
		free(process);
	}
}

void		free_all_process(t_process *process)
{
	t_process	*next;

	while (process->prev)
		process = process->prev;
	while (process)
	{
		next = process->next;
		free_process(process);
		process = next;
	}
}

void		free_job(t_job	*job)
{
	if (job)
	{
		if (job->prev)
			job->prev->next = job->next;
		if (job->next)
			job->next->prev = job->prev;
		if (job->line)
			free(job->line);
		if (job->list)
			free_all_process(job->list);
		free(job);
	}
}

void		free_all_job(t_job *job)
{
	t_job	*next;

	while (job->prev)
		job = job->prev;
	while (job)
	{
		next = job->next;
		free_job(job);
		job = next;
	}
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
		if (job_is_finish(nav))
		{
			if (head == nav)
			{
				g_job_head = next;
				head = g_job_head;
			}
			free_job(nav);
		}
		nav = next;
	}
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
    					p->is_stopped = 1;
    				else
    				{
    					p->is_finish = 1;
						if (WIFSIGNALED(status))
        					ft_dprintf(3, "%d: Terminated by signal %d.\n", (int)pid, WTERMSIG(p->status));
						p->ret = status;
        			}
        			return (0);
        		}
				p = p->next;
			}
			j = j->next;
		}
		ft_dprintf(3, "No child process %d.\n", pid);
      	return(-1);
    }
	else if (pid == 0)
		return(-1);
	else
	{
		ft_dprintf(3, "waitpid err\n");
		return(-1);
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
	pid_t	pid;

    pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status) && !job_is_stopped(job) && !job_is_completed(job))
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
}

void		put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(0, job->pgid);
	if (cont)
	{
    	restore_term(1);
    	if (kill(-job->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)"); //attention fonction interdite
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
