/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:35:54 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:06:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOK_RULES_H
# define FT_TOK_RULES_H
t_chr_class		get_chr_class[255] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_SEMI,
	//['\n'] = CHR_VALIDATOR,

	['#'] = CHR_COMMENT,
	['A' ... 'Z'] = CHR_WORD,
	['a' ... 'z'] = CHR_WORD,
	['0' ... '9'] = CHR_DIGIT,
	['_'] = CHR_WORD,
	['='] = CHR_WORD,
	[':'] = CHR_WORD,

	['~'] = CHR_WORD,

	['/'] = CHR_WORD,

	['.'] = CHR_WORD,

	['['] = CHR_WORD,
	[']'] = CHR_WORD,
	['@'] = CHR_WORD,
	[','] = CHR_WORD,
	
	['{'] = CHR_RBRACE,
	['}'] = CHR_LBRACE,
	//['$'] = CHR_EXP,
	['('] = CHR_RPAREN,
	[')'] = CHR_LPAREN,

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

int		ABSTRACT_TOKEN[TOK_MAX] = {
	[TOK_REDIRECTION] = 1, // >> <<
	[TOK_PIPE] = 1, // | ||
	[TOK_OPERATOR] = 1 // = == &&
};

t_toktype	token_chr_rules[TOK_MAX][CHR_MAX] = {
	[TOK_SP] = {[CHR_SP] = 0,},
	[TOK_WORD] = {
		[CHR_WORD] = 1,
		[CHR_DIGIT] = 1,
		[CHR_ESCAPE] = 1,
		[CHR_DASH] = 1
	},
	[TOK_IO_NUMBER] = {[CHR_DIGIT] = 1,},
	[TOK_BANG] = {[CHR_BANG] = 1,},
	[TOK_SQUOTE] = {
		[CHR_SP ... CHR_AND] = 1,
	},
	[TOK_DQUOTE] = {
		[CHR_SP ... CHR_AND] = 1,
	},
	[TOK_OPERATOR] = {[CHR_AND] = 1, [CHR_SEMI] = 1},
	[TOK_REDIRECTION] = {[CHR_RREDI ... CHR_LREDI] = 1, [CHR_PIPE] = 1, [CHR_DASH] = 1, [CHR_AND] = 1},
	[TOK_PIPE] = {[CHR_PIPE] = 1},
	[TOK_VALIDATOR] = {[CHR_VALIDATOR] = 1},
};

t_toktype	get_tok_type[CHR_MAX] = {
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
	[CHR_SQUOTE] = TOK_SQUOTE,
	[CHR_DQUOTE] = TOK_DQUOTE,
	//[CHR_EXP] = TOK_EXP,
	[CHR_AND] = TOK_OPERATOR,
	[CHR_SEMI] = TOK_OPERATOR,
	[CHR_LPAREN] = TOK_LPAREN,
	[CHR_RPAREN] = TOK_RPAREN,
	[CHR_NEWLINE] = TOK_NEWLINE
};

const char	DEBUG_TOKEN[TOK_MAX][30] = {
	[TOK_SP] = "TOK_SP",
	[TOK_WORD] = "TOK_WORD",
	[TOK_VALIDATOR] = "TOK_VALIDATOR",
	//[TOK_OPERATOR] = "TOK_OPERATOR",
	[TOK_AND_IF] = "TOK_AND_IF",
	[TOK_AND] = "TOK_AND",
	[TOK_OR_IF] = "TOK_OR_IF",
	//[TOK_REDIRECTION] = "TOK_REDIRECTION",
	[TOK_LREDI] = "TOK_LREDI",
	[TOK_RREDI] = "TOK_RREDI",
	[TOK_DLESS] = "TOK_DLESS",
	[TOK_DGREAT] = "TOK_DGREAT",
	[TOK_ESCAPE] = "TOK_WORD",
	[TOK_SQUOTE] = "TOK_SQUOTE",
	[TOK_DQUOTE] = "TOK_DQUOTE",
	[TOK_SUBSHELL] = "TOK_SUBSHELL",
	[TOK_SUBSTITUTION] = "TOK_SUBSTITUTION",
	//[TOK_EXP] = "TOK_EXPANSION",
	[TOK_PIPE] = "TOK_PIPE"
};

const char	DEBUG_CHR[CHR_MAX][30] = {
	[CHR_SP] = "CHR_SP",
	[CHR_WORD] = "CHR_WORD",
	[CHR_VALIDATOR] = "CHR_VALIDATOR",
	//[CHR_OPERATOR] = "CHR_OPERATOR",
	[CHR_ESCAPE] = "CHR_ESCAPE",
	[CHR_PIPE] = "CHR_PIPE",
	[CHR_SQUOTE] = "CHR_SQUOTE",
	[CHR_DQUOTE] = "CHR_DQUOTE",
	[CHR_COMMENT] = "CHR_COMMENT",
	//[CHR_REDIRECTION] = "CHR_REDIRECTION"
};
#endif
