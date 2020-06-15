/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:11:03 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 18:37:29 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_pipe_sequence(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	if ((node = parse_command(sh)))
	{
		tok = sh->tok;
		while (tok.tok == TOK_PIPE)
		{
			sh->tok = get_next_token(sh->input, sh->stack.errors);
			if ((nod2 = parse_command(sh)))
				node = save_node(node, tok, nod2, 3);
			else
			{
				free(tok.data);
				error_push(sh->stack.errors, PARSE_ERROR, sh->tok.data);
				return (node);
			}
			tok = sh->tok;
		}
	}
	return (node);
}
