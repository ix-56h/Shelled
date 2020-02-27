/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 23:28:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/26 23:29:54 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"
#include "ft_printf.h"
#include "visitor.h"

int		ft_debug_job(char **argv, char ***tenv)
{
	t_job		*job;
	t_process	*process;
	int			i;

	i = 0;
	job = g_job_head;
	while (job)
	{
		process = job->data;
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
				ft_printf("\tret: %i\t", process->ret);
				ft_printf("\tfinish: %i\n", (int)process->is_finish);
				process = process->next;
			}
			++i;
		}
		job = job->next;
	}
	return (0);
}
