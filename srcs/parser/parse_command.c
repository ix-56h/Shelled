/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:11:22 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:11:24 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_command(t_sh *sh)
{
	t_node	*node;
	t_node	*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_simple_command(sh)))
		return (node);
	else if ((node = parse_compound_command(sh)))
	{
		if ((nod2 = parse_redirect_list(sh)))
			node = push_node_left(node, nod2);
	}
	else
		node = parse_function_definition(sh);
	return (node);
}
