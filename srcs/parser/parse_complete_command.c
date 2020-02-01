/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_complete_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:09:43 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 06:19:33 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_complete_command(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_list(sh)))
	{
		while ((nod2 = parse_list(sh)))
			node = binnode(node, nod2, nod2->right);
		if ((nod2 = parse_separator_op(sh)))
			node = binnode(node, nod2, nod2->right);
	}
	return (node);
}
