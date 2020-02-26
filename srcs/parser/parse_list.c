/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/26 07:59:25 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node    *parse_list(t_sh *sh)
{
	t_node			*node;
	t_node			*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_separator_op(sh)))
		{
			if (node->right)
				node->right = binnode(node->right, nod2, NULL);
			else
				node = binnode(node, nod2, NULL);
			if ((nod2 = parse_and_or(sh)))
			{
				if (node->right)
					binnode(node->right->left, node->right, nod2);
				else
					binnode(node->left, node, nod2);
			}
		}
	}
	return (node);
}
