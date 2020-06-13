/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:26:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 02:18:39 by akeiflin         ###   ########.fr       */
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

static int	return_err_job_misc(int err, pid_t pid)
{
	if (err == 1)
		ft_dprintf(3, "No child process %d.\n", pid);
	else if (err == 2)
		ft_dprintf(3, "waitpid err\n");
	return (-1);
}

static int	sub_mark_process(t_process **p, t_job **j, int status, pid_t pid)
{
	if ((*p)->pid == pid)
	{
		(*p)->status = status;
		if (WIFSTOPPED(status))
		{
			(*p)->is_stopped = 1;
			(*j)->is_notified = 0;
		}
		else
		{
			(*p)->is_finish = 1;
			(*p)->ret = status;
		}
		return (0);
	}
	(*p) = (*p)->next;
	return (1);
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
				if (!sub_mark_process(&p, &j, status, pid))
					return (0);
			j = j->next;
		}
		return (return_err_job_misc(1, pid));
	}
	else if (pid == 0)
		return (-1);
	else
		return (return_err_job_misc(2, pid));
}

void		wait_for_job(t_job *job)
{
	int		status;
	char	*exit_status;
	pid_t	pid;

	if (job_is_completed(job) ||
			(pid = waitpid(WAIT_ANY, &status, WUNTRACED)) == -1)
		return ;
	if (WIFEXITED(status))
	{
		exit_status = ft_itoa(WEXITSTATUS(status));
		add_set("?", exit_status);
		free(exit_status);
	}
	while (!mark_process_status(pid, status)
				&& !job_is_stopped(job) && !job_is_completed(job))
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
