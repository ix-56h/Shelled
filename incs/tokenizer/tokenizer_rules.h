/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:48 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/02 11:11:16 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_RULES_H
# define TOKENIZER_RULES_H

static const t_chr_class		g_get_chr_class[255] =
{
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_SEMI,
	['$'] = CHR_DOL,
	['#'] = CHR_WORD,
	['A'...'Z'] = CHR_WORD,
	['a'...'z'] = CHR_WORD,
	['0'...'9'] = CHR_DIGIT,
	['%'] = CHR_WORD,
	['+'] = CHR_WORD,
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
	['{'] = CHR_LBRACE,
	['}'] = CHR_RBRACE,
	[')'] = CHR_RPAREN,
	['('] = CHR_LPAREN,
	['*'] = CHR_WORD,
	['-'] = CHR_DASH,
	['\\'] = CHR_ESCAPE,
	['\n'] = CHR_NEWLINE,
	['<'] = CHR_LREDI,
	['>'] = CHR_RREDI,
	['|'] = CHR_PIPE,
	['!'] = CHR_WORD,
	['\''] = CHR_SQUOTE,
	['"'] = CHR_DQUOTE,
	['&'] = CHR_AND,
	['?'] = CHR_WORD
};

static const int				g_abstract_token[TOK_MAX] =
{
	[TOK_REDIRECTION] = 1,
	[TOK_PIPE] = 1,
	[TOK_AND] = 1,
	[TOK_SEMI] = 1
};

static const int				g_token_chr_rules[TOK_MAX][CHR_MAX] =
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
		[CHR_RPAREN] = 0,
		[CHR_LBRACE] = 1,
		[CHR_RBRACE] = 0,
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
		[CHR_RPAREN] = 0,
		[CHR_LBRACE] = 1,
		[CHR_RBRACE] = 0,
		[CHR_DOL] = 1,
		[CHR_DASH] = 1
	},
	[TOK_IO_NUMBER] = {
		[CHR_DIGIT] = 1
	},
	[TOK_BANG] = {
		[CHR_BANG] = 1
	},
	[TOK_AND] = {
		[CHR_AND] = 1
	},
	[TOK_SEMI] = {
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

static const t_toktype		g_get_tok_type[CHR_MAX] = {
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
	[CHR_AND] = TOK_AND,
	[CHR_SEMI] = TOK_SEMI,
	[CHR_LPAREN] = TOK_LPAREN,
	[CHR_RPAREN] = TOK_RPAREN,
	[CHR_LBRACE] = TOK_LBRACE,
	[CHR_RBRACE] = TOK_RBRACE,
	[CHR_NEWLINE] = TOK_NEWLINE
};
#endif
