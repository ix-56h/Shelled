/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_suffix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:17:04 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:17:05 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_cmd_suffix(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_WORD)
	{
		node = save_node(NULL, tok, NULL, ARGS);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		while ((tok = sh->tok).tok == TOK_WORD)
		{
			nod2 = save_node(NULL, tok, NULL, 0);
			node = binnode(NULL, nod2, node);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
	}
	else if ((nod2 = parse_io_redirect(sh)))
		return (nod2);
	return (node);
}
