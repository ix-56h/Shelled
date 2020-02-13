/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:48 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/13 21:57:47 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_RULES_H
# define TOKENIZER_RULES_H

static t_chr_class		g_get_chr_class[255] =
{
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_SEMI,
	['$'] = CHR_DOL,
	['#'] = CHR_COMMENT,
	['A'...'Z'] = CHR_WORD,
	['a'...'z'] = CHR_WORD,
	['0'...'9'] = CHR_DIGIT,
	['_'] = CHR_WORD,
	['='] = CHR_WORD,
	[':'] = CHR_WORD,
	['`'] = CHR_BQUOTE,
	['~'] = CHR_WORD,
	['/'] = CHR_WORD,
	['.'] = CHR_WORD,
	['['] = CHR_WORD,
	[']'] = CHR_WORD,
	['@'] = CHR_WORD,
	[','] = CHR_WORD,
	['{'] = CHR_RBRACE,
	['}'] = CHR_LBRACE,
	['*'] = CHR_WORD,
	['-'] = CHR_DASH,
	['\\'] = CHR_ESCAPE,
	['\n'] = CHR_NEWLINE,
	['<'] = CHR_LREDI,
	['>'] = CHR_RREDI,
	['|'] = CHR_PIPE,
	['!'] = CHR_BANG,
	['\''] = CHR_SQUOTE,
	['"'] = CHR_DQUOTE,
	['&'] = CHR_AND
};

static int				g_abstract_token[TOK_MAX] =
{
	[TOK_REDIRECTION] = 1,
	[TOK_PIPE] = 1,
	[TOK_OPERATOR] = 1
};

static int				g_token_chr_rules[TOK_MAX][CHR_MAX] =
{
	[TOK_SP] = {
		[CHR_SP] = 0
	},
	[TOK_WORD] = {
		[CHR_WORD] = 1,
		[CHR_DIGIT] = 1,
		[CHR_ESCAPE] = 1,
		[CHR_SQUOTE] = 1,
		[CHR_DQUOTE] = 1,
		[CHR_BQUOTE] = 1,
		[CHR_LPAREN] = 1,
		[CHR_DOL] = 1,
		[CHR_DASH] = 1
	},
	[TOK_ASSIGNMENT_WORD] = {
		[CHR_WORD] = 1,
		[CHR_DIGIT] = 1,
		[CHR_ESCAPE] = 1,
		[CHR_SQUOTE] = 1,
		[CHR_DQUOTE] = 1,
		[CHR_BQUOTE] = 1,
		[CHR_LPAREN] = 1,
		[CHR_DOL] = 1,
		[CHR_DASH] = 1
	},
	[TOK_IO_NUMBER] = {
		[CHR_DIGIT] = 1
	},
	[TOK_BANG] = {
		[CHR_BANG] = 1
	},
	[TOK_OPERATOR] = {
		[CHR_AND] = 1,
		[CHR_SEMI] = 1
	},
	[TOK_REDIRECTION] = {
		[CHR_RREDI] = 1,
		[CHR_LREDI] = 1,
		[CHR_PIPE] = 1,
		[CHR_AND] = 1
	},
	[TOK_PIPE] = {
		[CHR_PIPE] = 1
	}
};

static t_toktype		g_get_tok_type[CHR_MAX] = {
	[CHR_SP] = TOK_SP,
	[CHR_WORD] = TOK_WORD,
	[CHR_ESCAPE] = TOK_WORD,
	[CHR_DASH] = TOK_WORD,
	[CHR_DIGIT] = TOK_WORD,
	[CHR_BANG] = TOK_BANG,
	[CHR_VALIDATOR] = TOK_VALIDATOR,
	[CHR_LREDI] = TOK_REDIRECTION,
	[CHR_RREDI] = TOK_REDIRECTION,
	[CHR_PIPE] = TOK_PIPE,
	[CHR_SQUOTE] = TOK_WORD,
	[CHR_DQUOTE] = TOK_WORD,
	[CHR_BQUOTE] = TOK_WORD,
	[CHR_DOL] = TOK_WORD,
	[CHR_AND] = TOK_OPERATOR,
	[CHR_SEMI] = TOK_OPERATOR,
	[CHR_LPAREN] = TOK_LPAREN,
	[CHR_RPAREN] = TOK_RPAREN,
	[CHR_NEWLINE] = TOK_NEWLINE
};
#endif
