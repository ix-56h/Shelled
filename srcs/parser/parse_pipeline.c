/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:47 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:10:47 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_pipeline(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_BANG)
	{
		if ((node = parse_pipe_sequence(sh)))
			node = save_node(node, sh->tok, NULL, 4);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	else
		node = parse_pipe_sequence(sh);
	return (node);
}
