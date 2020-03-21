/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linebreak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:22:49 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 16:47:25 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		parse_linebreak(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (0);
	node = NULL;
	if ((node = parse_newline_list(sh)))
		free(node);
	return (1);
}
