/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 14:30:38 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_rules.h"
#include "error_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int			get_token(char *s, t_chr_class chr_class \
			, t_lifo *stack, t_tokens *tok)
{
	t_chr_class	prev_class;
	int			anchor;
	t_toktype	toktype;

	prev_class = chr_class;
	anchor = 0;
	toktype = get_tok_type[prev_class];
	if (is_special_char(chr_class, prev_class)
		&& lex_sequence(s, &anchor, stack) == 0)
		return (anchor);
	while (s[anchor] && (prev_class == CHR_ESCAPE || token_chr_rules[toktype]
			[(chr_class = get_chr_class[(unsigned char)s[anchor]])]))
	{
		if (is_special_char(chr_class, prev_class))
		{
			if (!lex_sequence(s, &anchor, stack))
				return (anchor);
			continue;
		}
		prev_class = chr_class;
		anchor++;
	}
	((toktype == TOK_LPAREN || toktype == TOK_RPAREN) ? (anchor += 1) : 0);
	*tok = save_token(s, anchor, toktype);
	return (anchor);
}

t_tokens	get_next_token(char *s, t_lifo*stack)
{
	t_chr_class		chr_class = 0;
	t_toktype		toktype = 0;
	t_tokens		token;
	static int		i = 0;

	if (s[i] == '\0')
	{
		i = 0;
		return (save_token(s, 0, TOK_EOF));
	}
	if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
		return (token_error(UNRECOGNIZED_TOKEN, stack, s[i]));
	if (chr_class == CHR_COMMENT || chr_class == CHR_SP)
	{
		ignore_chr_class(s, &i, chr_class);
		return (get_next_token(s, stack));
	}
	if (!(toktype = get_tok_type[chr_class]))
		return (token_error(UNRECOGNIZED_TOKEN, stack, s[i]));
	i += get_token(s + i, chr_class, stack, &token);
	if (!lifo_empty(stack))
		return (token_error(0, stack, 0));
	if (token.tok == TOK_WORD && (s[i] == '>' || s[i] == '<') && (ft_isdigits(token.data)))
		token.tok = TOK_IO_NUMBER;
	if (ABSTRACT_TOKEN[token.tok] && !(token.tok = get_true_toktype(token.data, token.tok, &i)))
	{
		error_push(stack, UNRECOGNIZED_TOKEN, token.data);
		return (token_error(0, stack, 0));
	}
	return (token);
}
