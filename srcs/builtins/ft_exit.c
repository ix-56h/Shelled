/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:57:57 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/11 15:38:57 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"
#include "job.h"
#include "historique.h"
#include "ligne.h"
#include "hash.h"

void	clean_before_exit(void)
{
	restore_signals();
	clean_job();
	if (g_ready_exit)
		orphaned_jobs();
	free_historic();
	free_env(g_env);
	free_env(g_set);
	empty_table();
	restore_term(1);
}

int		check_if_jobs(void)
{
	t_job *job;

	job = g_job_head;
	while (job)
	{
		if (job_is_stopped(job) && !job_is_completed(job))
		{
			if (g_ready_exit == 1)
				return (0);
			g_ready_exit = 1;
			ft_putstr_fd("42sh: there are stopped job\n", 2);
			return (1);
		}
		job = job->next;
	}
	return (0);
}

int		check_num(char *argv)
{
	if (!argv)
		return (0);
	if (ft_isalldigit(argv) == 0)
	{
		ft_putstr_fd("42sh: exit: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	return (ft_atoi(argv));
}

int		ft_exit(char **argv, char ***tenv)
{
	int value;

	(void)tenv;
	ft_putstr_fd("exit\n", 1);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("42sh: exit: too much arguments\n", 2);
		return (1);
	}
	if (check_if_jobs() == 1)
		return (0);
	value = check_num(argv[1]);
	clean_before_exit();
	exit(value);
	return (0);
}
