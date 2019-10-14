/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_rules.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:35:54 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/14 16:23:03 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOK_RULES_H
# define FT_TOK_RULES_H
t_chr_class		get_chr_class[255] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_VALIDATOR,
	['\n'] = CHR_VALIDATOR,

	['#'] = CHR_COMMENT,
	['_'] = CHR_WORD,
	[':'] = CHR_WORD,
	['~'] = CHR_WORD,
	['/'] = CHR_WORD,
	['.'] = CHR_WORD,
	['['] = CHR_WORD,
	[']'] = CHR_WORD,
	['@'] = CHR_WORD,
	[','] = CHR_WORD,
	//['{'] = CHR_RBRACE,
	['{'] = CHR_WORD,
	//['}'] = CHR_LBRACE,
	['}'] = CHR_WORD,
	//['$'] = CHR_EXP,
	['$'] = CHR_WORD,
	//['('] = CHR_RSUB,
	['('] = CHR_WORD,
	//[')'] = CHR_LSUB,
	[')'] = CHR_WORD,

	['*'] = CHR_WORD,

	['A' ... 'Z'] = CHR_WORD,
	['a' ... 'z'] = CHR_WORD,
	['0' ... '9'] = CHR_DIGIT,
	
	['-'] = CHR_WORD,

	['\\'] = CHR_ESCAPE,
	
	['<'] = CHR_REDIRECTION,
	['>'] = CHR_REDIRECTION,

	['|'] = CHR_PIPE,

	['\''] = CHR_SQUOTE,
	['"'] = CHR_DQUOTE,
	
	['='] = CHR_OPERATOR,
	['&'] = CHR_OPERATOR
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
		[CHR_ESCAPE] = 1
	},
	[TOK_SQUOTE] = {
		[0 ... CHR_REDIRECTION] = 1,
	},
	[TOK_DQUOTE] = {
		[0 ... CHR_REDIRECTION] = 1,
	},
	[TOK_OPERATOR] = {[CHR_OPERATOR] = 1},
	[TOK_REDIRECTION] = {[CHR_REDIRECTION] = 1},
	[TOK_PIPE] = {[CHR_PIPE] = 1},
	[TOK_VALIDATOR] = {[CHR_VALIDATOR] = 1},
	//[TOK_EXP] = {},
	//[TOK_SUBSTITUTION] = {},
	//[TOK_SUBSHELL] = {}
};

t_toktype	get_tok_type[CHR_MAX] = {
	[CHR_SP] = TOK_SP,
	[CHR_WORD] = TOK_WORD,
	[CHR_DIGIT] = TOK_WORD,//not really word, but why not
	[CHR_VALIDATOR] = TOK_VALIDATOR,
	[CHR_ESCAPE] = TOK_WORD,
	[CHR_REDIRECTION] = TOK_REDIRECTION,
	[CHR_PIPE] = TOK_PIPE,
	[CHR_SQUOTE] = TOK_SQUOTE,
	[CHR_DQUOTE] = TOK_DQUOTE,
	[CHR_EXP] = TOK_EXP,
	//[CHR_RBRACE] = TOK_SUBSTITUTION,
	[CHR_LBRACE] = 0,
	//[CHR_RSUB] = TOK_SUBSHELL,
	[CHR_LSUB] = 0,
	[CHR_OPERATOR] = TOK_OPERATOR
};

const char	DEBUG_TOKEN[TOK_MAX][30] = {
	[TOK_SP] = "TOK_SP",
	[TOK_WORD] = "TOK_WORD",
	[TOK_VALIDATOR] = "TOK_VALIDATOR",
	[TOK_OPERATOR] = "TOK_OPERATOR",
	[TOK_REDIRECTION] = "TOK_REDIRECTION",
	[TOK_ESCAPE] = "TOK_WORD",
	[TOK_SQUOTE] = "TOK_SQUOTE",
	[TOK_DQUOTE] = "TOK_DQUOTE",
	[TOK_SUBSHELL] = "TOK_SUBSHELL",
	[TOK_SUBSTITUTION] = "TOK_SUBSTITUTION",
	[TOK_EXP] = "TOK_EXPANSION",
	[TOK_PIPE] = "TOK_PIPE"
};

const char	DEBUG_CHR[CHR_MAX][30] = {
	[CHR_SP] = "CHR_SP",
	[CHR_WORD] = "CHR_WORD",
	[CHR_VALIDATOR] = "CHR_VALIDATOR",
	[CHR_OPERATOR] = "CHR_OPERATOR",
	[CHR_ESCAPE] = "CHR_ESCAPE",
	[CHR_PIPE] = "CHR_PIPE",
	[CHR_SQUOTE] = "CHR_SQUOTE",
	[CHR_DQUOTE] = "CHR_DQUOTE",
	[CHR_COMMENT] = "CHR_COMMENT",
	[CHR_REDIRECTION] = "CHR_REDIRECTION"
};
#endif
