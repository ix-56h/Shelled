/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_tokenizer.c								:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:40:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void		increment_pointors(int *i, int *a)
{
	(*i)++;
	(*a)++;
}

int			lex_match_squote(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	while (s[*i] && s[*i] != '\'')
		increment_pointors(i, anchor);
	if (s[*anchor] != '\'')
	{
		printf("ntm \n");
		return (0);
	}
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_dquote(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '\'' || s[*i] == '$' || s[*i] == '`')
		{
			if (!lex_sequence(s, i, anchor))
				return (0);
			continue;
		}
		increment_pointors(i, anchor);
	}
	if (s[*anchor] != '"')
	{
		printf("ntm \n");
		return (0);
	}
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_bquote(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	while (s[*i] && s[*i] != '\'')
		increment_pointors(i, anchor);
	if (s[*anchor] != '\'')
	{
		printf("ntm \n");
		return (0);
	}
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_dol(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	while (s[*i] && s[*i] != '\'')
		increment_pointors(i, anchor);
	if (s[*anchor] != '\'')
	{
		printf("ntm \n");
		return (0);
	}
	increment_pointors(i, anchor);
	return (1);
}
