/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compound_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:11:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:11:44 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_compound_command(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if ((node = parse_brace_group(sh)))
		return (node);
	else if ((node = parse_subshell(sh)))
		return (node);
	else if ((node = parse_for_clause(sh)))
		return (node);
	else if ((node = parse_case_clause(sh)))
		return (node);
	else if ((node = parse_if_clause(sh)))
		return (node);
	else if ((node = parse_while_clause(sh)))
		return (node);
	else if ((node = parse_until_clause(sh)))
		return (node);
	return (node);
}
