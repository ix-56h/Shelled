/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_separator_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:23:17 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:23:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_separator_op(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_AND || tok.tok == TOK_SEMI)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}
