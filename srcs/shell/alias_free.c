/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_free.c                                       :+:      :+:    :+:   */
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

int		f_s(char **save_alias)
{
	free_env(save_alias);
	return (0);
}

char	*free_recursive(char *input_s, char **alias_cpy, char *alias_v)
{
	free(input_s);
	free_env(alias_cpy);
	return (alias_v);
}

void	free_alias(char **alias)
{
	int i;

	i = -1;
	while (alias[++i])
		free(alias[i]);
	free(alias);
}

char	*free_recursive_launch(char **pot_alias, char **save_alias,
		char **alias_cpy, char *new_input)
{
	free_alias(pot_alias);
	free_alias(save_alias);
	free_alias(alias_cpy);
	return (new_input);
}

void	reset_token(t_tokens token, int *is_multi, char *alias_v)
{
	char	*name;
	int		cpt;
	int		cpt2;

	name = get_value_by_name(token.data);
	if (name)
	{
		cpt2 = ft_strlen(alias_v);
		cpt = ft_strlen(name);
		if (cpt > 0)
		{
			if (alias_v[cpt2 - 1] == ' ')
				*is_multi = 0;
			else
				*is_multi = 1;
		}
		free(name);
	}
	if (token.tok == 12)
		*is_multi = 1;
	free(token.data);
}
