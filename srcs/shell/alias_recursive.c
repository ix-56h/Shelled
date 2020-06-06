/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_recursive.c                                  :+:      :+:    :+:   */
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

char	**del_var_alias(char **alias_cpy, char *data, char **alias_v, int *i)
{
	char *freed;

	print_with_alias(data, alias_v, i);
	freed = get_name(alias_cpy[is_alias(data, alias_cpy)]);
	alias_cpy = del_var(alias_cpy, freed);
	free(freed);
	return (alias_cpy);
}

char	**realloc_alias_n_multi(char **alias_cpy, char **save_alias\
									, int *is_multi)
{
	free_env(alias_cpy);
	alias_cpy = cpy_alias(save_alias);
	*is_multi = 0;
	return (alias_cpy);
}

int		ft_strcmp_alias(char *s1, char *s2)
{
	int		i;
	char	d;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	d = s1[i] - s2[i];
	if (d == 0)
		free(s1);
	return (d);
}

char	**init_recursive(int *is_multi, char **input_s,
		char **alias_cpy, char *alias_v)
{
	char	**save_alias;

	*is_multi = 0;
	*input_s = ft_strdup(alias_v);
	save_alias = cpy_alias(alias_cpy);
	free(alias_v);
	return (save_alias);
}

char	*recursive_alias(char *alias_v, char **alias_cpy, t_lifo *stack)
{
	t_tokens	token;
	char		**save_alias;
	char		*input_s;
	int			i;
	int			is_multi;

	i = 0;
	if (check_conform(alias_cpy, alias_v) == 0)
		return (alias_v);
	save_alias = init_recursive(&is_multi, &input_s, alias_cpy, alias_v);
	while ((token = get_next_token(input_s, stack)).data)
	{
		if (ft_strcmp_alias(token.data, "EOF") == 0)
			break ;
		if (token.tok != 12)
			alias_cpy = realloc_alias_n_multi(alias_cpy, save_alias, &is_multi);
		if (is_multi == 0 && is_alias(token.data, alias_cpy) >= 0)
			alias_cpy = del_var_alias(alias_cpy, token.data, &alias_v, &i);
		else
			alias_v = join_new_input(token.data, alias_v, &i);
		reset_token(token, &is_multi, alias_v);
	}
	if (f_s(save_alias) == 0 && alias_cpy && ft_strcmp(alias_v, input_s) != 0)
		alias_v = recursive_alias(alias_v, cpy_env(alias_cpy), stack);
	return (free_recursive(input_s, alias_cpy, alias_v));
}
