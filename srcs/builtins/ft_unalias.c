/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "libft.h"
#include "ft_printf.h"

void	free_realloc_alias(char *name_g, char *name, char *value)
{
	free(name_g);
	free(name);
	free(value);
}

int		unalias_error(int mod, char *arg)
{
	if (mod == 0)
		ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
	else if (mod == 1)
	{
		ft_putstr_fd("unalias: no such hash table element: ", 2);
		ft_putendl_fd(arg, 2);
	}
	return (1);
}

int		del_all(void)
{
	int		cpt;
	char	*name;

	cpt = ft_tablen(g_alias) - 1;
	while (cpt > -1)
	{
		name = get_name(g_alias[cpt]);
		g_alias = del_var(g_alias, name);
		free(name);
		cpt--;
	}
	free(g_alias);
	g_alias = NULL;
	return (0);
}

int		del_alias(char *arg, char ***env)
{
	int		cpt;
	char	*name;

	cpt = -1;
	(void)env;
	while (g_alias[++cpt])
	{
		name = get_name(g_alias[cpt]);
		if (ft_strcmp(name, arg) == 0)
		{
			g_alias = del_var(g_alias, name);
			free(name);
			return (2);
		}
		free(name);
	}
	return (1);
}

int		ft_unalias(char **args, char ***env)
{
	int		cpt;
	int		opt;

	cpt = 0;
	opt = 0;
	if (!g_alias)
	{
		while (args[++cpt])
			unalias_error(1, args[cpt]);
		return (1);
	}
	if (ft_tablen(args) == 1)
		return (unalias_error(0, NULL));
	while (args[++cpt])
	{
		if (ft_strcmp("-a", args[cpt]) == 0 && opt == 0)
			return (del_all());
		if (ft_strcmp("--", args[cpt]) == 0 || cpt == 1)
			opt = 1;
		if (opt == 1)
			unalias_error(del_alias(args[cpt], env), args[cpt]);
	}
	if (ft_tablen(g_alias) == 0)
		g_alias = NULL;
	return (0);
}
