/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wexp_tokenizer.c								:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:40:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "wexp_rules.h"
#include "libft.h"

int			lex_sequence(char *s, int *i, int *anchor)
{
	int				ret = 0;

	if (s[*anchor] == '\'')
		ret = lex_match_squote(s, i, anchor);
	else if (s[*anchor] == '"')
		ret = lex_match_dquote(s, i, anchor);
	else if (s[*anchor] == '`')
		ret = lex_match_command_sub(s, i, anchor);
	else if (s[*anchor] == '$')
		ret = lex_match_dol(s, i, anchor);
	return (ret);
}

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
		return (0);
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_dquote(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	while (s[*i] && s[*i] != '"')
	{
		//if (s[*i] == '\'' || s[*i] == '$' || s[*i] == '`')
		if (wexp_rules[DQU][s[*i]])
		{
			if (!lex_sequence(s, i, anchor))
				return (0);
			continue;
		}
		increment_pointors(i, anchor);
	}
	if (s[*anchor] != '"')
		return (0);
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_command_sub(char *s, int *i, int *anchor)
{
	char	close;

	close = (s[*i] == '`' ? '`' : ')');
	increment_pointors(i, anchor);
	if (is_whitespace(s[*i]))
	{
		skip_whitespaces(s, i, anchor);
		if (s[*i] == '(')
		{
			if (!lex_match_command_sub(s, i, anchor))
				return (0);
		}
	}
	while (s[*i] && s[*i] != close)
	{
		if (s[*i] == '(' || s[*i] == '`')
		{
			if (!lex_match_command_sub(s, i, anchor))
				return (0);
		}
		if (wexp_rules[BQU][s[*i]])
		{
			if (!lex_sequence(s, i, anchor))
				return (0);
			continue;
		}
		increment_pointors(i, anchor);
	}
	if (s[*anchor] != close)
		return (0);
	increment_pointors(i, anchor);
	return (1);
}

int		lex_match_dol(char *s, int *i, int *anchor)
{
	increment_pointors(i, anchor);
	if (s[*i] == '(')
	{
		if (lex_match_command_sub(s, i, anchor))
		{
			skip_whitespaces(s, i, anchor);
			return (1);
		}
	}
	else if (ft_isalpha(s[*i]) || s[*i] == '_')
	{
		increment_pointors(i, anchor);
		while (ft_isalpha(s[*i]) || s[*i] == '_' || ft_isdigit(s[*i]))
			increment_pointors(i, anchor);
		return (1);
	}
	return (0);
}
