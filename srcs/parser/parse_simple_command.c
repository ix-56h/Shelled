/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:15:51 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 12:15:52 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_simple_command(t_sh *sh)
{
	t_node	*node;
	t_node	*nod2;
	t_node	*args;
	t_node	*first;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	first = NULL;
	if ((node = parse_cmd_prefix(sh)))
	{
		first = node;
		while ((nod2 = parse_cmd_prefix(sh)))
			node = binnode(node, nod2, nod2->right);
		if ((nod2 = parse_cmd_word(sh)))
		{
			args = nod2;
			push_args(args, ft_strdup(args->data));
			while (sh->tok.tok == TOK_WORD)
			{
				push_args(args, sh->tok.data);
				sh->tok = get_next_token(sh->input, sh->stack.errors);
			}
			binnode(nod2, first, first->right);
			if ((nod2 = parse_cmd_suffix(sh)))
			{
				first = nod2;
				node = binnode(node, nod2, nod2->right);
				while ((nod2 = parse_cmd_prefix(sh)))
					node = binnode(node, nod2, nod2->right);
			}
			while (sh->tok.tok == TOK_WORD)
			{
				push_args(args, sh->tok.data);
				sh->tok = get_next_token(sh->input, sh->stack.errors);
			}
		}
	}
	else if ((node = parse_cmd_name(sh)))
	{
		args = node;
		push_args(args, ft_strdup(args->data));
		while (sh->tok.tok == TOK_WORD)
		{
			push_args(args, sh->tok.data);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
		if ((nod2 = parse_cmd_suffix(sh)))
		{
			first = nod2;
			node = binnode(node, nod2, nod2->right);
			while ((nod2 = parse_cmd_prefix(sh)))
				node = binnode(node, nod2, nod2->right);
		}
		while (sh->tok.tok == TOK_WORD)
		{
			push_args(args, sh->tok.data);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
	}
	return (node);
}
