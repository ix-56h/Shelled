/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:38 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 17:38:05 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ignore_arithmetic(char *s, int *a)
{
	while (s[*a])
	{
		if (s[*a] == '(')
		{
			while (s[*a] && s[*a] != ')')
				(*a)++;
			if (s[*a] != ')')
				return (0);
			(*a)++;
		}
		else if (s[*a] == ')')
			return (1);
		(*a)++;
	}
	return (0);
}

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
