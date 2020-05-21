/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
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
#include "tokenizer.h"

int		is_alias(char *t_alias, char **cpy_alias)
{
	int		cpt;
	char	*name;

	cpt = -1;
	while (cpy_alias[++cpt])
	{
		name = get_name(cpy_alias[cpt]);
		if (ft_strcmp(name, t_alias) == 0)
		{
			free(name);
			return (cpt);
		}
		free(name);
	}
	return (-1);
}

char	*launch_recursive(char *alias_v, char **alias_cpy, t_lifo *stack)
{
	t_tokens	token;
	char		**save_alias;
	char		**pot_alias;
	int			i;

	i = 0;
	save_alias = cpy_alias(alias_cpy);
	while ((token = get_next_token(alias_v, stack)).data)
	{
		if (ft_strcmp(token.data, "EOF") == 0)
		{
			free(token.data);
			break ;
		}
		pot_alias = alloc_pot(token.data, pot_alias, &i);
	}
	free(alias_v);
	return (print_recursive_alias(alias_cpy, save_alias, pot_alias, stack));
}

char	*test_alias(char *alias_n, t_lifo *stac)
{
	char	*name_g;
	char	*c;
	int		cpt;
	char	**alias_cpy;

	cpt = -1;
	alias_cpy = cpy_alias(g_alias);
	while (g_alias[++cpt])
	{
		name_g = get_name(g_alias[cpt]);
		if (ft_strcmp(name_g, alias_n) == 0)
		{
			alias_cpy = del_var(alias_cpy, name_g);
			c = launch_recursive(get_value(g_alias[cpt])\
					, cpy_alias(alias_cpy), stac);
			free_env(alias_cpy);
			free(name_g);
			return (c);
		}
		free(name_g);
	}
	free_env(alias_cpy);
	return (NULL);
}

char	*add_alias(char *input, t_lifo *stack)
{
	t_tokens	token;
	char		**pot_alias;
	int			*toktype;
	int			is_multi;
	int			i;

	if (!g_alias)
		return (input);
	i = 0;
	toktype = 0;
	is_multi = 0;
	while ((token = get_next_token(input, stack)).data)
	{
		if (ft_strcmp(token.data, "EOF") == 0)
		{
			free(token.data);
			if (i == 0)
				return (input);
			break ;
		}
		toktype = alloc_toktype(toktype, &is_multi, token);
		pot_alias = alloc_pot(token.data, pot_alias, &i);
	}
	free(input);
	return (print_new_input(pot_alias, toktype, stack));
}
