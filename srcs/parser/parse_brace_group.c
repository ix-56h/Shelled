/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_brace_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:20:15 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/24 16:20:58 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_brace_group(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_LBRACE)
	{
		tok = sh->tok;
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if ((node = parse_compound_list(sh)))
		{
			if (sh->tok.tok == TOK_RBRACE)
			{
				free(sh->tok.data);
				node->state = GRP;
				sh->tok = get_next_token(sh->input, sh->stack.errors);
			}
			else
				error_push(sh->stack.errors, PARSE_ERROR, sh->tok.data);
		}
		free(tok.data);
	}
	return (node);
}
