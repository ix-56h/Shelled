/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:40:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/06 20:11:50 by akeiflin         ###   ########.fr       */
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

t_builtin lookforbuiltin_v2(char *data)
{
	if (ft_strcmp(data, "set") == 0)
		return (ft_set);
	else if (ft_strcmp(data, "unset") == 0)
		return (ft_unset);
	else if (ft_strcmp(data, "type") == 0)
		return (ft_type);
	else if (ft_strcmp(data, "alias") == 0)
		return (ft_alias);
	else if (ft_strcmp(data, "unalias") == 0)
		return (ft_unalias);
	else if (ft_strcmp(data, "test") == 0)
		return (ft_test);
	return (NULL);
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
	return (lookforbuiltin_v2(data));
}
