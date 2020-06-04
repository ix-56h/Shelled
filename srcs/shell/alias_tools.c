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

#include "sh.h"
#include "builtins.h"
#include "ft_printf.h"

char	**add_pot(char **alias, char *pot)
{
	size_t		i;
	size_t		j;
	char		**new_env;

	j = 0;
	i = 0;
	while (alias && alias[i])
		++i;
	i += 2;
	new_env = ft_calloc(sizeof(char *) * i);
	while (j < i - 2)
	{
		new_env[j] = alias[j];
		j++;
	}
	alias = ft_free(alias);
	new_env[j] = ft_strdup(pot);
	return (new_env);
}

char	**alloc_pot(char *data, char **pot_alias, int *i)
{
	if (*i == 0)
	{
		if (!(pot_alias = (char**)malloc(sizeof(char*) * 2)))
			return (NULL);
		pot_alias[0] = ft_strdup(data);
		pot_alias[1] = NULL;
		*i = *i + 1;
	}
	else
	{
		pot_alias = add_pot(pot_alias, data);
		*i = *i + 1;
	}
	free(data);
	return (pot_alias);
}

char	**cpy_alias(char **alias)
{
	char	**new_alias;
	int		i;

	i = 0;
	while (alias[i])
		i++;
	if (!(new_alias = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (alias[++i])
		new_alias[i] = ft_strdup(alias[i]);
	new_alias[i] = NULL;
	return (new_alias);
}

int		check_for_replace(char *arg)
{
	int		cpt;
	char	*name;

	name = get_value_by_name(arg);
	if (name)
	{
		cpt = ft_strlen(name);
		if (cpt > 0)
		{
			if (name[cpt - 1] == ' ')
			{
				free(name);
				return (0);
			}
		}
		free(name);
	}
	return (1);
}

int		*alloc_toktype(int *toktype, int *is_multi, char **pot, t_tokens token)
{
	int i;

	i = 0;
	if (*is_multi == 1)
	{
		while (toktype[i] != 0)
			i++;
		if (*is_multi == 1 && toktype[i - 1] == 2)
			*is_multi = check_for_replace(pot[i - 1]);
	}
	if (*is_multi == 0 && token.tok == 12)
	{
		toktype = create_n_realloc_type(toktype, *is_multi);
		*is_multi = 1;
	}
	else
	{
		toktype = create_n_realloc_type(toktype, *is_multi);
		if (token.tok != 12)
			*is_multi = 0;
	}
	return (toktype);
}
