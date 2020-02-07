/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:17:54 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 18:36:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_io_file(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_LREDI || tok.tok == TOK_LESSAND \
		|| tok.tok == TOK_RREDI || tok.tok == TOK_GREATAND \
		|| tok.tok == TOK_DGREAT || tok.tok == TOK_LESSGREAT \
		|| tok.tok == TOK_CLOBBER)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		node = save_node(NULL, tok, NULL, IO_REDIRECT);
		if ((nod2 = parse_filename(sh)))
			node = binnode(NULL, node, nod2);
		else
			error_push(sh->stack.errors, PARSE_ERROR, tok.data);
	}
	return (node);
}
