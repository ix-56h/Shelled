/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:09:54 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/11 15:33:34 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AST_H
# define FT_AST_H
#include "../includes/tokenizer.h"
#include "../includes/tokenizer_rules.h"
typedef enum	e_state{
	S_MIN,
	S_DEFAULT,
	S_PIPE,
	S_REDIRECTION,
	S_DQUOTES,
	S_SQUOTES,
	S_SUBSHELL,
	S_MAX
}				t_state;

t_state			GET_STATE[TOK_MAX] = {
	[TOK_SQUOTE] = S_SQUOTES,
	[TOK_DQUOTE] = S_DQUOTES,
	[TOK_VALIDATOR] = S_DEFAULT,
	[TOK_WORD] = S_DEFAULT
};

typedef struct			s_astnode {
	t_toktype			token;
	char				*literal;
	struct s_astnode	*l;
	struct s_astnode	*r;
}						t_astnode;

#endif
