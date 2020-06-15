/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:28 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 20:02:27 by niguinti         ###   ########.fr       */
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
	if ((node = parse_pipeline(sh)) && lifo_empty(sh->stack.errors))
	{
		tok = sh->tok;
		while (tok.tok == TOK_AND_IF || tok.tok == TOK_OR_IF)
		{
			sh->tok = get_next_token(sh->input, sh->stack.errors);
			if ((nod2 = parse_pipeline(sh)))
				node = save_node(node, tok, nod2, 0);
			else
			{
				node = save_node(node, tok, nod2, 0);
				if (lifo_empty(sh->stack.errors))
					error_push(sh->stack.errors, PARSE_ERROR, sh->tok.data);
				return (node);
			}
			tok = sh->tok;
		}
	}
	return (node);
}
