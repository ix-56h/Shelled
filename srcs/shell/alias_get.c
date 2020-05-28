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
	char	*value;
	int		cpt;

	cpt = -1;
	while (g_alias[++cpt])
	{
		name_g = get_name(g_alias[cpt]);
		if (ft_strcmp(name_g, name) == 0)
		{
			free(name_g);
			value = get_value(g_alias[cpt]);
			if (ft_strlen(value) > 0)
				return (value);
			free(value);
			return (ft_strdup(""));
		}
		free(name_g);
	}
	return (NULL);
}
