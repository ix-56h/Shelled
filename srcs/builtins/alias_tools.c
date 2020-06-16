/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_tools.c                                      :+:      :+:    :+:   */
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

char		*get_name(char *arg)
{
	int		cpt;
	char	*name;

	cpt = 0;
	while (arg[cpt] != '=' && arg[cpt])
		cpt++;
	if (!(name = (char*)malloc(sizeof(char) * (cpt + 1))))
		return (NULL);
	cpt = 0;
	while (arg[cpt] != '=' && arg[cpt])
	{
		name[cpt] = arg[cpt];
		cpt++;
	}
	name[cpt] = '\0';
	return (name);
}

char		*get_value(char *arg)
{
	int		cpt;
	int		ind;
	int		i;
	char	*value;

	if (!arg)
		return (NULL);
	cpt = 0;
	i = 0;
	ind = ft_strlen(arg);
	while (arg[cpt] != '=' && arg[cpt])
		cpt++;
	if (cpt == ind)
		return (NULL);
	if (!(value = (char *)malloc(sizeof(char) * (ind - cpt + 1))))
		return (NULL);
	cpt++;
	while (cpt < ind)
	{
		value[i] = arg[cpt];
		i++;
		cpt++;
	}
	value[i] = '\0';
	return (value);
}

void		ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void		sort_alias(void)
{
	int	cpt;

	cpt = 0;
	while (g_alias[cpt + 1])
	{
		if (ft_strcmp(g_alias[cpt], g_alias[cpt + 1]) > 0)
		{
			ft_swap(&g_alias[cpt], &g_alias[cpt + 1]);
			cpt = 0;
		}
		else
			cpt++;
	}
}
