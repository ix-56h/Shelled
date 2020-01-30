/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:28 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:10:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_and_or(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_pipeline(sh)))
	{
		while ((nod2 = parse_pipeline(sh)))
			node = binnode(node, nod2, nod2->left);
			//node = binnode(node->left, node, nod2);
		while ((tok = sh->tok).tok == TOK_AND_IF || tok.tok == TOK_OR_IF)
		{
			sh->tok = get_next_token(sh->input, sh->stack.errors);
			if ((nod2 = parse_pipeline(sh)))
				node = save_node(node, tok, nod2, 5);
			else
			{
				node = save_node(node, tok, nod2, 0);
				error_push(sh->stack.errors, PARSE_ERROR_NEAR, tok.data);
				return (node);
			}
		}
	}
	return (node);
}
