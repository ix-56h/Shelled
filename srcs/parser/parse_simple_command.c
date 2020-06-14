/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:15:51 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 06:11:41 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_simple_command_misc_prefix(t_sh *sh, t_node **node, \
		t_node **args, t_node **nod2)
{
	while ((*nod2 = parse_cmd_prefix(sh)))
		*node = push_node_left(*nod2, *node);
	while ((*nod2 = parse_cmd_word(sh)))
	{
		*args = *nod2;
		push_args(*args, ft_strdup((*args)->data));
		while (sh->tok.tok == TOK_WORD)
		{
			push_args(*args, sh->tok.data);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
		push_node_left(*nod2, *node);
		while ((*nod2 = parse_cmd_suffix(sh)))
			*node = binnode(*node, *nod2, (*nod2)->right);
	}
}

void	parse_simple_command_cmd_name_misc(t_sh *sh, t_node **node, \
		t_node **args, t_node **nod2)
{
	*args = *node;
	push_args(*args, ft_strdup((*args)->data));
	while (sh->tok.tok == TOK_WORD || sh->tok.tok == TOK_ASSIGNMENT_WORD)
	{
		push_args(*args, sh->tok.data);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	while ((*nod2 = parse_io_redirect(sh)))
		*node = binnode(*node, *nod2, (*nod2)->right);
	while (sh->tok.tok == TOK_WORD || sh->tok.tok == TOK_ASSIGNMENT_WORD)
	{
		push_args(*args, sh->tok.data);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
}

t_node	*parse_simple_command(t_sh *sh)
{
	t_node	*node;
	t_node	*nod2;
	t_node	*args;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_cmd_prefix(sh)))
		parse_simple_command_misc_prefix(sh, &node, &args, &nod2);
	else if ((node = parse_cmd_name(sh)))
		parse_simple_command_cmd_name_misc(sh, &node, &args, &nod2);
	return (node);
}
