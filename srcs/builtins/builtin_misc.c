/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:40:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/11 13:35:39 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int			count_arg(char **argv)
{
	int	i;

	i = -1;
	while (*argv)
	{
		++i;
		++argv;
	}
	return (i);
}

t_builtin	lookforbuiltin(char *data)
{
	if (ft_strcmp(data, "addpath") == 0)
		return (ft_addpath);
	else if (ft_strcmp(data, "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(data, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(data, "setenv") == 0)
		return (ft_setenv);
	else if (ft_strcmp(data, "take") == 0)
		return (ft_take);
	else if (ft_strcmp(data, "unsetenv") == 0)
		return (ft_unsetenv);
	else if (ft_strcmp(data, "exit") == 0)
		return (ft_exit);
	else if (ft_strcmp(data, "djob") == 0)
		return (ft_debug_job);
	else if (ft_strcmp(data, "return") == 0)
		return (ft_return);
	else if (ft_strcmp(data, "set") == 0)
		return (ft_set);
	else if (ft_strcmp(data, "unset") == 0)
		return (ft_unset);
	else if (ft_strcmp(data, "export") == 0)
		return (ft_export);
	else if (ft_strcmp(data, "bg") == 0)
		return (ft_bg);
	else if (ft_strcmp(data, "jobs") == 0)
		return (ft_jobs);
	else if (ft_strcmp(data, "fg") == 0)
		return(ft_fg);
	return (NULL);
}
