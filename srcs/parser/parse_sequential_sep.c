/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequential_sep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:24:12 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/31 23:34:25 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_sequential_sep(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_SEMI)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if (parse_linebreak(sh))
			node = save_node(NULL, tok, NULL, 0);
	}
	else if ((node = parse_newline_list(sh)))
	{
		free(node);
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}
