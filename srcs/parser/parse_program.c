/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:59:08 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 18:00:37 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_program(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((parse_linebreak(sh) == 1) && (node = parse_complete_commands(sh)))
	{
		if (!lifo_empty(sh->stack.errors))
			return (node);
		if ((parse_linebreak(sh) == 0) || (sh->tok.tok != TOK_EOF))
			error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
	}
	else if ((parse_linebreak(sh) == 0) || sh->tok.tok != TOK_EOF)
		error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
	return (node);
}
