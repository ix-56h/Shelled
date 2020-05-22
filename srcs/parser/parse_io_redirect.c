/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:17:39 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 05:55:58 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_io_redirect(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_IO_NUMBER)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if ((node = parse_io_file(sh))
			|| (node = parse_io_here(sh)))
		{
			node->io = ft_atoi(tok.data);
			free(tok.data);
		}
	}
	else if ((node = parse_io_file(sh))
			|| (node = parse_io_here(sh)))
		return (node);
	return (node);
}
