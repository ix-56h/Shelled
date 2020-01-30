/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:23:34 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:23:35 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_separator(t_sh *sh)
{
	t_node		*node;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if ((node = parse_separator_op(sh)))
		return (node);
	else if ((node = parse_newline_list(sh)))
		return (node);
	return (node);
}
