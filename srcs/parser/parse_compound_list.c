/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compound_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:12:18 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 20:09:53 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_compound_list(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if (parse_linebreak(sh) == 1)
	{
		if ((node = parse_term(sh)))
		{
			if ((nod2 = parse_separator(sh)))
				node = binnode(node, nod2, NULL);
		}
	}
	return (node);
}
