/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/02 01:33:08 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum	e_toktype {
	TOK_SP,
	TOK_WORD,
	TOK_VALIDATOR,
	TOK_OPERATOR,
	TOK_NEWLINE,
	TOK_REDIRECTION,
	TOK_ESCAPE,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_PIPE
} t_toktype;

typedef enum	e_chr_class {
	CHR_SP,
	CHR_WORD,
	CHR_VALIDATOR,
	CHR_ESCAPE,
	CHR_OPERATOR,
	CHR_PIPE,
	CHR_SQUOTE,
	CHR_DQUOTE,
	CHR_REDIRECTION
} t_chr_class;


t_chr_class		get_chr_class[256] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_VALIDATOR,
	['\n'] = CHR_VALIDATOR,

	['A' ... 'Z'] = CHR_WORD,
	['a' ... 'z'] = CHR_WORD,
	['0' ... '9'] = CHR_WORD,

	['\\'] = CHR_ESCAPE,
	
	['<'] = CHR_REDIRECTION,
	['>'] = CHR_REDIRECTION,

	['|'] = CHR_PIPE,

	['\''] = CHR_SQUOTE,
	['"'] = CHR_DQUOTE,
	
	['='] = CHR_OPERATOR
};

t_toktype	get_tok_type[CHR_REDIRECTION + 1] = {
	[CHR_SP] = TOK_SP,
	[CHR_WORD] = TOK_WORD,
	[CHR_VALIDATOR] = TOK_VALIDATOR,
	[CHR_ESCAPE] = TOK_ESCAPE,
	[CHR_REDIRECTION] = TOK_REDIRECTION,
	[CHR_PIPE] = TOK_PIPE,
	[CHR_SQUOTE] = TOK_SQUOTE,
	[CHR_DQUOTE] = TOK_DQUOTE,
	[CHR_OPERATOR] = TOK_OPERATOR
};

const char	DEBUG_TOKEN[TOK_PIPE + 1][30] = {
	[TOK_SP] = "TOK_SP",
	[TOK_WORD] = "TOK_WORD",
	[TOK_VALIDATOR] = "TOK_VALIDATOR",
	[TOK_OPERATOR] = "TOK_OPERATOR",
	[TOK_NEWLINE] = "TOK_NEWLINE",
	[TOK_REDIRECTION] = "TOK_REDIRECTION",
	[TOK_ESCAPE] = "TOK_ESCAPE",
	[TOK_SQUOTE] = "TOK_SQUOTE",
	[TOK_DQUOTE] = "TOK_DQUOTE",
	[TOK_PIPE] = "TOK_PIPE"
};

const char	DEBUG_CHR[CHR_REDIRECTION + 1][30] = {
	[CHR_SP] = "CHR_SP",
	[CHR_WORD] = "CHR_WORD",
	[CHR_VALIDATOR] = "CHR_VALIDATOR",
	[CHR_OPERATOR] = "CHR_OPERATOR",
	[CHR_ESCAPE] = "CHR_ESCAPE",
	[CHR_PIPE] = "CHR_PIPE",
	[CHR_SQUOTE] = "CHR_SQUOTE",
	[CHR_DQUOTE] = "CHR_DQUOTE",
	[CHR_REDIRECTION] = "CHR_REDIRECTION"
};
