/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:38:17 by niguinti         ###   ########.fr       */
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
