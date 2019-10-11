/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:54:25 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/11 14:59:40 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEX_H
# define FT_LEX_H
typedef enum	e_shellstates{
	S_DEFAULT,
	S_PIPE,
	S_REDIRECTION,
	S_DQUOTES,
	S_SQUOTES,
	S_SUBSHELL
}				t_shellstates;

t_shellstates	states[S_SUBSHELL + 1][TOK_PIPE + 1] = {
	[S_DEFAULT] = { [TOK_WORD] = 1, },
	[S_PIPE] = { [TOK_WORD] = 1, },
	[S_REDIRECTION] = { [TOK_WORD] = 1, },
	[S_DQUOTES] = { [TOK_WORD] = 1, },
	[S_SQUOTES] = { [TOK_WORD] = 1, },
};

typedef struct			s_ast
{
	t_toktype			tok;
	char				*literal;
	struct t_toktype	*l;
	struct t_toktype	*r;
}						t_ast;

t_ast	*lex_tokens(t_tokens *tok_list);
#endif
