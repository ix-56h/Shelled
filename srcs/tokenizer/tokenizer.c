/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/24 16:26:04 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_rules.h"
#include "error_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int			is_grouping_tok(t_toktype t)
{
	if (t == TOK_LPAREN || t == TOK_RPAREN
		|| t == TOK_RBRACE || t == TOK_LBRACE)
		return (1);
	return (0);
}

t_toktype	get_true_toktype(char *s, t_toktype toktype, int *i)
{
	size_t	l;
	int		ret;

	ret = TOK_ERROR;
	l = ft_strlen(s);
	if (toktype == TOK_OPERATOR)
		ret = check_operator(s, l, i);
	else if (toktype == TOK_PIPE)
		ret = check_pipe(s, l, i);
	else if (toktype == TOK_REDIRECTION)
		ret = check_redirections(s, l, i);
	return (ret);
}

int			get_token(char *s, t_gnt *g, t_lifo *stack)
{
	t_chr_class	prev_class;
	int			anchor;

	anchor = 0;
	prev_class = g->chr_class;
	g->toktype = g_get_tok_type[prev_class];
	g->toktype == TOK_NEWLINE ? anchor++ : 0;
	if (is_special_char(g->chr_class, prev_class) \
		&& lex_sequence(s, &anchor, stack) == 0)
		return (anchor);
	while (s[anchor] && (g_token_chr_rules[g->toktype][(g->chr_class = \
g_get_chr_class[(unsigned char)s[anchor]])] || prev_class == CHR_ESCAPE))
	{
		if (is_special_char(g->chr_class, prev_class))
		{
			if (!lex_sequence(s, &anchor, stack))
				return (anchor);
			continue;
		}
		prev_class = g->chr_class;
		anchor++;
	}
	is_grouping_tok(g->toktype) ? (anchor += 1) : 0;
	g->token = save_token(s, anchor, g->toktype);
	return (anchor);
}

int			init_and_post_process(char *s, t_gnt *gnt, t_lifo *stack)
{
	gnt->chr_class = 0;
	if (s[gnt->i] == '\0')
	{
		gnt->i = 0;
		gnt->token = save_token(s, 0, TOK_EOF);
		return (1);
	}
	if (!(gnt->chr_class = g_get_chr_class[(unsigned char)s[gnt->i]]))
	{
		gnt->token = token_error(UNRECOGNIZED_TOKEN, stack, s[gnt->i]);
		return (1);
	}
	return (0);
}

t_tokens	get_next_token(char *s, t_lifo *stack)
{
	t_gnt	*gnt;

	gnt = gnt_standalone(1);
	if (init_and_post_process(s, gnt, stack) == 1)
		return (gnt->token);
	if (gnt->chr_class == CHR_COMMENT || gnt->chr_class == CHR_SP)
	{
		ignore_chr_class(s, &(gnt->i), gnt->chr_class);
		return (get_next_token(s, stack));
	}
	if (!(gnt->toktype = g_get_tok_type[gnt->chr_class]))
		return (token_error(UNRECOGNIZED_TOKEN, stack, s[gnt->i]));
	gnt->i += get_token(s + gnt->i, gnt, stack);
	if (!lifo_empty(stack))
		return (token_error(0, stack, 0));
	if (gnt->token.tok == TOK_WORD && (s[gnt->i] == '>' || s[gnt->i] == '<') \
		&& (ft_isdigits(gnt->token.data)))
		gnt->token.tok = TOK_IO_NUMBER;
	if (g_abstract_token[gnt->token.tok] && !(gnt->token.tok = \
				get_true_toktype(gnt->token.data, gnt->token.tok, &(gnt->i))))
	{
		error_push(stack, UNRECOGNIZED_TOKEN, gnt->token.data);
		return (token_error(0, stack, 0));
	}
	return (gnt->token);
}
