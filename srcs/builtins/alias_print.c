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

/*
**  mod = 0 : print error not good alias name to print
**  mod = 1 : name error not conform alias name
*/

int			error_alias(char *arg, int mod)
{
	if (mod == 0)
	{
		ft_putstr_fd("42sh: alias: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not found\n", 2);
	}
	else if (mod == 1)
	{
		ft_putstr_fd("42sh: alias: \'", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("\': invalid alias name", 2);
	}
	return (0);
}

void		show_this_alias(char *arg)
{
	int		cpt;
	char	*name;

	cpt = -1;
	while (g_alias[++cpt])
	{
		name = get_name(g_alias[cpt]);
		if (ft_strcmp(arg, name) == 0)
		{
			ft_putendl_fd(g_alias[cpt], 1);
			free(name);
			return ;
		}
		free(name);
	}
	if ((name = get_value(arg)) == NULL)
		error_alias(arg, 0);
	free(name);
}

void		show_alias(void)
{
	int		ind;

	if (!g_alias)
		return ;
	ind = -1;
	while (g_alias[++ind])
		ft_putendl_fd(g_alias[ind], 1);
}

int			dispatch_show(int cpt, char ***env)
{
	(void)env;
	if (cpt == 1)
		show_alias();
	sort_alias();
	return (0);
}
