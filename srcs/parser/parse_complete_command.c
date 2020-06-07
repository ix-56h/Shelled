/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_complete_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:09:43 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/27 01:21:06 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_complete_command(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = parse_list(sh);
	return (node);
}
