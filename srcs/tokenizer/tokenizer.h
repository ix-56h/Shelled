/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/01 05:33:06 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

typedef enum	e_toktype {
	TOK_SP,
	TOK_ALPHA,
	TOK_SPECIAL,
	TOK_VALIDATOR,
	TOK_NEWLINE
} t_toktype;

typedef enum	e_chr_class {
	CHR_SP,
	CHR_WORD,
	CHR_SPECIAL,
	CHR_VALIDATOR
} t_chr_class;


t_toktype		get_current_tok_type[256] = {
	[' '] = CHR_SP,
	['\t'] = CHR_SP,
	[';'] = CHR_VALIDATOR,
	['\n'] = CHR_VALIDATOR,

	['A' ... 'Z'] = CHR_WORD,
	['a' ... 'z'] = CHR_WORD,
}
