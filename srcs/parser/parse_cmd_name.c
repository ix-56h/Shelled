/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:16:09 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/22 02:41:44 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_cmd_name(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_WORD)
	{
		if (!ft_strchr(sh->tok.data, '='))
		{
			applie_rule_one(sh->input, &sh->tok);
			node = save_node(NULL, sh->tok, NULL, ARGS);
		}
		else
			node = applie_7b(&(sh->tok), sh->tok.data);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return (node);
}
