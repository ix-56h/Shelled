/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_print.c                                      :+:      :+:    :+:   */
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

int		check_red(char *data)
{
	if (!ft_strcmp(">>", data))
		return (0);
	if (!ft_strcmp(">", data))
		return (0);
	if (!ft_strcmp("<<", data))
		return (0);
	if (!ft_strcmp("<", data))
		return (0);
	return (1);
}

void	print_with_alias(char *data, char **alias_v, int *i)
{
	char		*freed;
	static int	save;

	if (check_red(data) == 0)
		save = *i;
	if (*i == 0)
	{
		freed = get_value_by_name(data);
		*alias_v = ft_strdup(freed);
		free(freed);
	}
	else
	{
		if ((save != *i && save != *i - 1) || *i < 1)
			*alias_v = ft_strjoinf(*alias_v, " ", 1);
		*alias_v = ft_strjoinf(*alias_v, get_value_by_name(data), 3);
	}
	if (*i > save)
		save = 0;
	*i = *i + 1;
}

char	*join_new_input(char *data, char *new_input, int *i)
{
	static int save;

	if (save == 0)
		save = -2;
	if (check_red(data) == 0)
		save = *i;
	if (*i == 0)
		new_input = ft_strdup(data);
	else
	{
		if (save != *i && save != *i - 1)
			new_input = ft_strjoinf(new_input, " ", 1);
		new_input = ft_strjoinf(new_input, data, 1);
	}
	if (*i > save)
		save = -2;
	*i = *i + 1;
	return (new_input);
}

char	*print_recursive_alias(char **a_y, char **alias[2], t_lifo *sta,
					int *toktype)
{
	int		cpt;
	int		i;
	char	*new_input;
	char	*t;

	cpt = -1;
	i = 0;
	while (alias[1][++cpt])
	{
		if (toktype[cpt] == 2 && is_alias(alias[1][cpt], a_y) >= 0)
		{
			t = recursive_alias(ft_strdup(alias[1][cpt]), cpy_alias(a_y), sta);
			if (t)
			{
				new_input = join_new_input(t, new_input, &i);
				free(t);
				free_alias(a_y);
				a_y = cpy_alias(alias[0]);
			}
		}
		else
			new_input = join_new_input(alias[1][cpt], new_input, &i);
	}
	free(toktype);
	return (free_recursive_launch(alias[1], a_y, alias[0], new_input));
}

char	*print_new_input(char **pot_alias, int *toktype, t_lifo *stack)
{
	char	*to_add;
	char	*new_input;
	int		i;
	int		cpt;

	cpt = 0;
	i = 0;
	while (pot_alias[cpt])
	{
		if (toktype[cpt] == 2)
			to_add = test_alias(pot_alias[cpt], stack);
		if (to_add)
		{
			new_input = join_new_input(to_add, new_input, &i);
			free(to_add);
		}
		else
			new_input = join_new_input(pot_alias[cpt], new_input, &i);
		free(pot_alias[cpt]);
		to_add = NULL;
		cpt++;
	}
	free(toktype);
	free(pot_alias);
	return (new_input);
}
