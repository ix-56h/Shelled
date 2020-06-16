/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:46 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/11 22:51:48 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "wexp_rules.h"
#include "libft.h"
#include "stack.h"

int	lex_match_parameter(char *s, int *anchor, t_lifo *stack)
{
	while (s[*anchor] && s[*anchor] != '}')
	{
		if (g_wexp_rules[BQU][(int)(s[*anchor])])
		{
			if (!lex_sequence(s, anchor, stack))
				return (0);
			continue;
		}
		*anchor += 1;
	}
	if (s[*anchor] != '}')
	{
		error_push(stack, MATCH_LEX, "}");
		return (0);
	}
	*anchor += 1;
	return (1);
}

int	lex_match_squote(char *s, int *anchor, t_lifo *stack)
{
	*anchor += 1;
	while (s[*anchor] && s[*anchor] != '\'')
		*anchor += 1;
	if (s[*anchor] != '\'')
	{
		error_push(stack, MATCH_LEX, "'");
		return (0);
	}
	*anchor += 1;
	return (1);
}

int	lex_match_dquote(char *s, int *anchor, t_lifo *stack)
{
	unsigned int esc;

	*anchor += 1;
	esc = 0;
	while (s[*anchor] && (s[*anchor] != '"' || esc))
	{
		if (s[*anchor] == '\\' && !esc)
			esc = 1;
		else if (g_wexp_rules[DQU][(int)(s[*anchor])])
		{
			if (!lex_sequence(s, anchor, stack))
				return (0);
			continue;
		}
		else if (esc)
			esc = 0;
		*anchor += 1;
	}
	if (s[*anchor] != '"')
	{
		error_push(stack, MATCH_LEX, "\"");
		return (0);
	}
	*anchor += 1;
	return (1);
}

int	lex_match_command_sub(char *s, int *anchor, t_lifo *stack)
{
	char	close;

	close = (s[*anchor] == '`' ? '`' : ')');
	while (s[*anchor] && s[*anchor] != close)
	{
		if (g_wexp_rules[BQU][(int)(s[*anchor])])
		{
			if (!lex_sequence(s, anchor, stack))
				return (0);
			continue;
		}
		*anchor += 1;
	}
	if (s[*anchor] != close)
	{
		error_push(stack, MATCH_LEX, (close == '`') ? "`" : ")");
		return (0);
	}
	*anchor += 1;
	return (1);
}

int	lex_match_dol(char *s, int *anchor, t_lifo *stack)
{
	*anchor += 1;
	if (s[*anchor] == '(')
	{
		if (is_arithmetic(s + *anchor + 1))
			ignore_arithmetic(s, anchor);
		else if (!lex_match_command_sub(s, anchor, stack))
			return (0);
	}
	else if (s[*anchor] == '{')
	{
		if (!lex_match_parameter(s, anchor, stack))
			return (0);
	}
	else if (ft_isalpha(s[*anchor]) || s[*anchor] == '_' || s[*anchor] == '$')
	{
		*anchor += 1;
		while (ft_isalpha(s[*anchor]) || s[*anchor] == '_'
				|| ft_isdigit(s[*anchor]) || s[*anchor] == '$')
			*anchor += 1;
	}
	return (1);
}
