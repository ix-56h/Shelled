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

char	*print_no_after(char *before, char *value)
{
	char	*input;

	input = ft_strjoin(before, value);
	return (input);
}

char	*print_before_and_after(char *before, char *value, char *after)
{
	char	*input;

	input = ft_strjoin(before, value);
	input = ft_strjoinf(input, after, 1);
	return (input);
}

char	*print_no_before(char *value, char *after)
{
	char	*input;

	input = ft_strjoin(value, after);
	return (input);
}


char	*new_input(char *alias_v, char *input, int *cpt, int len_n)
{
	char	*after;
	char	*before;
	char	*new_input;

	after = get_after(input, *cpt + len_n);
	before = get_before(input, *cpt);
	if (!after && !before)
		new_input = ft_strdup(alias_v);
	else if (after && !before /* *cpt == 0 */)
	{
		new_input = print_no_before(alias_v, after);
		free(after);
	}
	else if (before && !after  /*ft_strlen(input) == (size_t)(*cpt + len_n)*/)
	{
		new_input = print_no_after(before, alias_v);
		free(before);
	}
	else
	{
		new_input = print_before_and_after(before, alias_v, after);
		free(after);
		free(before);
	}
	*cpt += ft_strlen(alias_v);
	free(input);
	return (new_input);
}

void rm_first_space(char *input)
{
	int cpt;
	int id;

	cpt = 0;
	id = 0;
	while (input[cpt] == ' ' || input[cpt] == '\t' || input[cpt] == '\n')
		cpt++;
	if (cpt == 0)
		return ;
	while (input[cpt])
	{
		input[id] = input[cpt];
		id++;
		cpt++;
	}
	input[id] = '\0';
}
