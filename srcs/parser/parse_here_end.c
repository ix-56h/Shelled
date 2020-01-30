/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:21:30 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:21:32 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_here_end(t_sh *sh)
{
	t_node		*node;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_WORD)
	{
		node = save_node(NULL, sh->tok, NULL, DEFAULT_ID);
		// rule 3  -> applie quote removal for get the true delimiter
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return(node);
}
