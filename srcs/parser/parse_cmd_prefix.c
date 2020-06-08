/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:16:44 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:16:46 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_cmd_prefix(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	if (sh->tok.tok == TOK_ASSIGNMENT_WORD)
	{
		node = save_node(NULL, sh->tok, NULL, ASSIGNMENT_WORD);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		while (sh->tok.tok == TOK_ASSIGNMENT_WORD)
		{
			nod2 = save_node(NULL, sh->tok, NULL, ASSIGNMENT_WORD);
			push_node_left(nod2, node);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
	}
	else if ((node = parse_io_redirect(sh)))
		return (node);
	return (node);
}
