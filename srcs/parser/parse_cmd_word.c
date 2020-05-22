/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:16:27 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 00:42:15 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_cmd_word(t_sh *sh)
{
	t_node		*node;
	char		*s2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	s2 = sh->tok.data;
	node = NULL;
	if (sh->tok.tok == TOK_WORD)
	{
		node = applie_7b(&(sh->tok), s2);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return (node);
}
