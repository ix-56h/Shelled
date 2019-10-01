/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/01 22:35:30 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

typedef enum	e_toktype {
	TOK_SP,
	TOK_WORD,
	TOK_VALIDATOR,
	TOK_OPERATOR,
	TOK_NEWLINE,
	TOK_ESCAPE
} t_toktype;

typedef enum	e_chr_class {
	CHR_SP,
	CHR_WORD,
	CHR_VALIDATOR,
	CHR_ESCAPE,
	CHR_OPERATOR,
	CHR_PIPE,
	CHR_SQUOTE,
	CHR_DQUOTE
} t_chr_class;


t_toktype		get_current_tok_type[256] = {
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
	
	['='] = CHR_OPERATOR,
	['&'] = CHR_OPERATOR
}
