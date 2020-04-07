/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "ft_printf.h"

char	*get_value_by_name(char *name)
{
	char	*name_g;
	int		cpt;

	cpt = -1;
	while (g_alias[++cpt])
	{
		name_g = get_name(g_alias[cpt]);
		if (ft_strcmp(name_g, name) == 0)
		{
			free(name_g);
			return (get_value(g_alias[cpt]));
		}
		free(name_g);
	}
	return (NULL);
}

char	*get_before(char *input, int cpt)
{
	int		id;
	char	*before;

	id = 0;
	if (cpt == 0)
		return (NULL);
	while (id < cpt)
		id++;
	if (!(before = (char*)malloc(sizeof(char) * (id + 1))))
		return (NULL);
	id = 0;
	while (id < cpt)
	{
		before[id] = input[id];
		id++;
	}
	before[id] = '\0';
	return (before);
}

char	*get_after(char *input, int cpt)
{
	char	*after;
	int		id;

	id = ft_strlen(input);
	if (cpt == id)
		return (NULL);
	if (!(after = (char*)malloc(sizeof(char) * (id - cpt + 1))))
		return (NULL);
	id = 0;
	while (input[cpt])
	{
		after[id] = input[cpt];
		id++;
		cpt++;
	}
	after[id] = '\0';
	return (after);
}
