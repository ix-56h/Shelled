/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:12:36 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/31 22:23:57 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_term(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_and_or(sh)))
			node = binnode(node, nod2, nod2->left);
	}
	if (node && (nod2 = parse_separator(sh)))
	{
		node = binnode(node, nod2, nod2->right);
		if ((nod2 = parse_and_or(sh)))
			node = binnode(node->left, node, nod2);
	}
	return (node);
}
