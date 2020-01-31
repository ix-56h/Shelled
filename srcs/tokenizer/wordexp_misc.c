/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:38 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 14:20:21 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_whitespaces(char *s, int *a)
{
	while (s[*a] && is_whitespace(s[*a]))
		(*a)++;
}

int		command_sub_skip_whitespaces(char *s, int *anchor, t_lifo *stack)
{
	*anchor += 1;
	if (is_whitespace(s[*anchor]))
	{
		skip_whitespaces(s, anchor);
		if (s[*anchor] == '(')
		{
			if (!lex_match_command_sub(s, anchor, stack))
				return (0);
		}
	}
	return (1);
}
