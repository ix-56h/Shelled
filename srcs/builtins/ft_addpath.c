/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:58:39 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 23:34:51 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"

static void		*free_in_tab(char **tab)
{
	while (*tab)
	{
		*tab = ft_free(*tab);
		++tab;
	}
	return (NULL);
}

static void		free_tab(char **tab)
{
	if (tab && *tab)
	{
		free_in_tab(tab);
		ft_free(tab);
	}
}

/*
**	Builtin: addpath
**	append the first argument on the PATH env entry
*/

int				ft_addpath(char **argv, char ***env)
{
	char	*path;
	char	*new_path;
	char	**new_arg;

	if (argv[1])
	{
		path = get_env(*env, "PATH");
		new_path = ft_vjoin(3, path, ":", argv[1]);
		new_arg = malloc(sizeof(char *) * 4);
		new_arg[0] = ft_strdup("setenv");
		new_arg[1] = ft_strdup("PATH");
		new_arg[2] = new_path;
		new_arg[3] = NULL;
		ft_setenv(new_arg, env);
		free_tab(new_arg);
	}
	else
		ft_putendl("addpath: Too few arguments");
	return (0);
}
