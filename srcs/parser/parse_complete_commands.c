/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_complete_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:09:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 18:35:36 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_complete_commands(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	if ((node = parse_complete_command(sh)))
	{
		(nod2 = parse_newline_list(sh)) ? free(nod2) : 0;
		while ((nod2 = parse_complete_command(sh)))
		{
			node = binnode(node, nod2, nod2->left);
			if ((nod2 = parse_newline_list(sh)))
			{
				free(nod2);
				if ((nod2 = parse_complete_command(sh)))
					node = binnode(node, nod2, nod2->right);
				else
				{
					error_push(sh->stack.errors, PARSE_ERROR, sh->tok.data);
					return (node);
				}
			}
		}
	}
	return (node);
}
