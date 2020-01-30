/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:10:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:10:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_list(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_node		*nod3;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	nod3 = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_separator_op(sh)))
		{
			if ((nod3 = parse_and_or(sh)))
				node = binnode(node, nod2, nod3);
			else
			{
				free(nod2->data);
				free(nod2);
			}
		}
	}
	return (node);
}
