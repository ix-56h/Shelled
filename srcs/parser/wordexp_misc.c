/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:38 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/19 06:36:38 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_whitespaces(char *s, int *i, int *a)
{
	while (s[*i] && is_whitespace(s[*i]))
	{
		(*i)++;
		(*a)++;
	}
}
