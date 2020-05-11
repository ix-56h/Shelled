/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:21:09 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/14 00:43:33 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_io_here(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if (sh->tok.tok == TOK_DLESS || sh->tok.tok == TOK_DLESSDASH)
	{
		tok = sh->tok;
		node = save_node(NULL, sh->tok, NULL, DEFAULT_ID);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if ((nod2 = parse_here_end(sh)))
		{
			node = binnode(NULL, node, nod2);
			fifo_insert(sh->stack.here_docs, node);
		}
		else
			error_push(sh->stack.errors, PARSE_ERROR, tok.data);
	}
	return (node);
}
