/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/27 01:48:41 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node		*parse_list(t_sh *sh)
{
	t_node			*root;
	t_node			*node;
	t_node			*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	root = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_separator_op(sh)))
		{
			!root ? root = nod2 : 0;
			if (node->right && (node->tok == TOK_AND || node->tok == TOK_SEMI))
			{
				binnode(node->right, nod2, NULL);
				binnode(node->left, node, nod2);
				node = nod2;
			}
			else
				node = binnode(node, nod2, NULL);
			if ((nod2 = parse_and_or(sh)))
				node = binnode(node->left, node, nod2);
		}
	}
	return (!root ? node : root);
}
