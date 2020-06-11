/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
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

void		stock_init_alias(char *n_alias, char *v_alias)
{
	g_alias[0] = ft_strjoinf(n_alias, "=", 1);
	g_alias[0] = ft_strjoinf(g_alias[0], v_alias, 3);
	g_alias[1] = NULL;
}

int			check_error_name(char *arg, int mod)
{
	int cpt;

	cpt = 0;
	while (arg[cpt] != '=' && arg[cpt])
	{
		if (ft_isalnum(arg[cpt]) == 1 || ft_isportable(arg[cpt]) == 1)
			cpt++;
		else
		{
			free(arg);
			if (mod == 0)
				error_alias(arg, 1);
			return (0);
		}
	}
	free(arg);
	return (1);
}

int			init_alias(char **args)
{
	int		cpt;
	char	*n_alias;
	char	*v_alias;

	cpt = 1;
	while ((v_alias = get_value(args[cpt])) == NULL
						|| check_error_name(get_name(args[cpt]), 0) == 0)
	{
		if (v_alias != NULL)
			free(v_alias);
		if (!args[cpt])
			return (0);
		if (check_error_name(get_name(args[cpt]), 1) == 1)
			error_alias(args[cpt], 0);
		cpt++;
	}
	free(v_alias);
	if (!(g_alias = (char**)malloc(sizeof(char*) * 2)))
		return (0);
	n_alias = get_name(args[cpt]);
	v_alias = get_value(args[cpt]);
	stock_init_alias(n_alias, v_alias);
	return (cpt);
}

void		realloc_alias(char *arg)
{
	int		ind;
	char	*name;
	char	*name_g;
	char	*value;

	ind = -1;
	if ((value = get_value(arg)) == NULL)
		return ;
	if (check_error_name(get_name(arg), 0) == 0)
		return ;
	name = get_name(arg);
	while (g_alias[++ind])
	{
		name_g = get_name(g_alias[ind]);
		if (ft_strcmp(name, name_g) == 0)
		{
			ft_edit_env(g_alias, name, value);
			free_realloc_alias(name_g, name, value);
			return ;
		}
		free(name_g);
	}
	g_alias = add_env(g_alias, name, value);
	free(name);
	free(value);
}

int			ft_alias(char **args, char ***env)
{
	static int	i;
	int			cpt;

	if (fcntl(1, F_GETFD) != 0)
		return (1);
	if (!g_alias)
	{
		i = 0;
		if (ft_tablen(args) == 1)
			return (1);
	}
	cpt = 0;
	while (args[++cpt])
	{
		if (i == 0)
		{
			if ((cpt = init_alias(args)) == 0)
				return (0);
			i++;
		}
		else
			realloc_alias(args[cpt]);
		show_this_alias(args[cpt]);
	}
	return (dispatch_show(cpt, env));
}
