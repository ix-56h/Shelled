/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_newline_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:22:32 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 17:40:02 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_newline_list(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_NEWLINE)
	{
		while (sh->tok.tok == TOK_NEWLINE)
		{
			tok = sh->tok;
			free(sh->tok.data);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}
