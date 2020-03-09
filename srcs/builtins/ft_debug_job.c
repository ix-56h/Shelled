/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 23:28:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/09 03:15:10 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"
#include "ft_printf.h"
#include "job.h"

int		ft_debug_job(char **argv, char ***tenv)
{
	t_job		*job;
	t_process	*process;
	int			i;

	(void)argv;
	(void)tenv;
	i = 0;
	job = g_job_head;
	while (job)
	{
		process = job->list;
		if (process)
		{
			ft_printf("job[%i]:\n", i);
			while (process)
			{
				if (process->pid == BUILTIN_JOB)
					ft_printf("\tpid: builtin\t");
				else if (process->pid == UNUSED_JOB)
					ft_printf("\tpid: unused\t");
				else
					ft_printf("\tpid: %i\t", process->pid);
				ft_printf("cmd: %s  ", process->command);
				ft_printf("ret: %i    ", process->ret);
				ft_printf("finish: %i   ", (int)process->is_finish);
				ft_printf("stoped: %i   \n", (int)process->is_stopped);
				process = process->next;
			}
			++i;
		}
		job = job->next;
	}
	return (0);
}
