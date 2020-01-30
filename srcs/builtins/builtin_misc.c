/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:40:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/30 06:57:19 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int		count_arg(char **argv)
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

t_builtin lookforbuiltin(char *data)
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
	else if (ft_strcmp(data, "env") == 0)
		return (ft_env);
	else if (ft_strcmp(data, "exit") == 0)
		return (ft_exit);
	return (NULL);
}
