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

#include "libft.h"
#include "sh.h"

int		check_conform(char **alias_cpy, char *alias_v)
{
	if (!alias_cpy)
		return (0);
	if (ft_strlen(alias_v) == 0)
	{
		free_env(alias_cpy);
		return (0);
	}
	return (1);
}

int		*realloc_type(int i, int is_multi, int *new_toktype)
{
	if (is_multi == 0)
		new_toktype[i++] = 2;
	else
		new_toktype[i++] = 1;
	new_toktype[i] = 0;
	return (new_toktype);
}

int		*create_n_realloc_type(int *toktype, int is_multi)
{
	int i;
	int *new_toktype;

	i = 0;
	if (toktype != 0)
	{
		while (toktype[i])
			i++;
		i += 2;
		if (!(new_toktype = (int*)malloc(sizeof(int) * i)))
			return (0);
		i = -1;
		while (toktype[++i])
			new_toktype[i] = toktype[i];
		free(toktype);
	}
	else
	{
		if (!(new_toktype = (int*)malloc(sizeof(int) * 2)))
			return (0);
	}
	return (realloc_type(i, is_multi, new_toktype));
}
