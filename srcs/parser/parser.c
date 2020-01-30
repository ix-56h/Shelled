/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:20 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 05:53:38 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expansions.h"

t_node	*parse_program(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((parse_linebreak(sh) == 1) && (node = parse_complete_commands(sh)))
	{
		if ((parse_linebreak(sh) == 0) || (sh->tok.tok != TOK_EOF))
			error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
	}
	else if (sh->tok.tok != TOK_EOF)
		error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
	return (node);
}

t_node	*parse_complete_commands(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_complete_command(sh)))
	{
		while ((nod2 = parse_complete_command(sh)))
			node = binnode(node->left, node, nod2);
		if ((nod2 = parse_newline_list(sh)))
		{
			free(nod2);
			if ((nod2 = parse_complete_command(sh)))
				node = binnode(node, nod2, NULL);
			else
			{
				error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
				return (node);
			}
		}
	}
	return (node);
}

t_node	*parse_complete_command(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_list(sh)))
	{
		while ((nod2 = parse_list(sh)))
		{
			printf("while parselist here\n");
			node = binnode(node, nod2, nod2->right);
		}
		if ((nod2 = parse_separator_op(sh)))
			node = binnode(node, nod2, nod2->right);
	}
	return (node);
}

t_node	*parse_list(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_node		*nod3;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	nod3 = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_separator_op(sh)))
		{
			if ((nod3 = parse_and_or(sh)))
				node = binnode(node, nod2, nod3);
			else
			{
				free(nod2->data);
				free(nod2);
			}
		}
	}
	return (node);
}

t_node	*parse_and_or(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_pipeline(sh)))
	{
		while ((nod2 = parse_pipeline(sh)))
			node = binnode(node, nod2, nod2->left);
		while ((tok = sh->tok).tok == TOK_AND_IF || tok.tok == TOK_OR_IF)
		{
			sh->tok = get_next_token(sh->input, sh->stack.errors);
			if ((nod2 = parse_pipeline(sh)))
				node = save_node(node, tok, nod2, 5);
			else
			{
				node = save_node(node, tok, nod2, 0);
				error_push(sh->stack.errors, PARSE_ERROR_NEAR, tok.data);
				return (node);
			}
		}
	}
	return (node);
}

t_node	*parse_pipeline(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_BANG)
	{
		if ((node = parse_pipe_sequence(sh)))
			node = save_node(node, sh->tok, NULL, 4);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	else
		node = parse_pipe_sequence(sh);
	return (node);
}

t_node	*parse_pipe_sequence(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_command(sh)))
	{
		tok = sh->tok;
		while (tok.tok == TOK_PIPE)
		{
			sh->tok = get_next_token(sh->input, sh->stack.errors);
			if ((nod2 = parse_command(sh)))
				node = save_node(node, tok, nod2, 3);
			else
			{
				error_push(sh->stack.errors, PARSE_ERROR_NEAR, tok.data);
				return (node);
			}
			tok = sh->tok;
		}
	}
	return (node);
}

t_node	*parse_command(t_sh *sh)
{
	t_node	*node;
	t_node	*nod2;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_simple_command(sh)))
		return (node);
	else if ((node = parse_compound_command(sh)))
	{
		if ((nod2 = parse_redirect_list(sh)))
			node = binnode(node, nod2, nod2->right);
	}
	else
		node = parse_function_definition(sh);
	return (node);
}

t_node	*parse_compound_command(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if ((node = parse_brace_group(sh)))
		return (node);
	else if ((node = parse_subshell(sh)))
		return (node);
	else if ((node = parse_for_clause(sh)))
		return (node);
	else if ((node = parse_case_clause(sh)))
		return (node);
	else if ((node = parse_if_clause(sh)))
		return (node);
	else if ((node = parse_while_clause(sh)))
		return (node);
	else if ((node = parse_until_clause(sh)))
		return (node);
	return (node);
}

t_node	*parse_subshell(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_LPAREN)
	{
		tok = sh->tok;
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if ((node = parse_compound_list(sh)))
		{
			if (sh->tok.tok == TOK_RPAREN)
			{
				free(sh->tok.data);
				node->state = SUBSH;
				sh->tok = get_next_token(sh->input, sh->stack.errors);
			}
			else
				error_push(sh->stack.errors, PARSE_ERROR_NEAR, sh->tok.data);
			free(tok.data);
		}
	}
	return (node);
}

t_node	*parse_compound_list(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;

	if ((node = parse_term(sh)))
	{
		if ((nod2 = parse_separator(sh)))
			node = binnode(node, nod2, nod2->left);
	}
	return (node);
}

t_node	*parse_term(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_and_or(sh)))
	{
		while ((nod2 = parse_and_or(sh)))
			node = binnode(node, nod2, nod2->left);
	}
	if (node && (nod2 = parse_separator(sh)))
	{
		node = binnode(node, nod2, nod2->right);
		if ((nod2 = parse_and_or(sh)))
			node = binnode(node->left, node, nod2);
	}
	return (node);
}

t_node	*parse_for_clause(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_name(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_in(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_wordlist(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_case_clause(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_case_list_ns(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_case_list(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_case_item_ns(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_case_item(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_pattern(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_if_clause(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_else_part(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_while_clause(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_until_clause(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_function_definition(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_function_body(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_fname(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_brace_group(t_sh *sh)
{
	return (NULL);
}

t_node	*parse_do_group(t_sh *sh)
{
	return (NULL);
}

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

t_node	*parse_cmd_name(t_sh *sh)
{
	t_node		*node;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_WORD)
	{
		if (!strchr(sh->tok.data, '='))
		{
			applie_rule_one(sh->input, &sh->tok);
			node = save_node(NULL, sh->tok, NULL, ARGS);
		}
		else
			node = applie_7b(&(sh->tok), sh->tok.data);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return(node);
}

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
	return(node);
}

t_node	*parse_cmd_prefix(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_ASSIGNMENT_WORD)
	{
		node = save_node(NULL, tok, NULL, ASSIGNMENT_WORD);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		while ((tok = sh->tok).tok == TOK_ASSIGNMENT_WORD)
		{
			nod2 = save_node(NULL, tok, NULL, ASSIGNMENT_WORD);
			node = binnode(NULL, nod2, node);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
	}
	else if ((node = parse_io_redirect(sh)))
		return (node);
	return (node);
}

t_node	*parse_cmd_suffix(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_WORD)
	{
		node = save_node(NULL, tok, NULL, ARGS);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		while ((tok = sh->tok).tok == TOK_WORD)
		{
			nod2 = save_node(NULL, tok, NULL, 0);
			node = binnode(NULL, nod2, node);
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
	}
	else if ((nod2 = parse_io_redirect(sh)))
		return (nod2);
	return (node);
}

t_node	*parse_redirect_list(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if ((node = parse_io_redirect(sh)))
	{
		while ((nod2 = parse_io_redirect(sh)))
			node = binnode(node, nod2, nod2->right);
	}
	return (node);
}

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

t_node	*parse_io_file(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_LREDI || tok.tok == TOK_LESSAND || tok.tok == TOK_RREDI
		|| tok.tok == TOK_GREATAND || tok.tok == TOK_DGREAT || tok.tok == TOK_LESSGREAT
		|| tok.tok == TOK_CLOBBER)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		node = save_node(NULL, tok, NULL, IO_REDIRECT);
		if ((nod2 = parse_filename(sh)))
			node = binnode(NULL, node, nod2);
		else
			error_push(sh->stack.errors, PARSE_ERROR_NEAR, tok.data);
	}
	return (node);
}

t_node	*parse_filename(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_WORD)
	{
		//rule 2
		// [Redirection to or from filename]
		//The expansions specified in Redirection shall occur. As specified there, exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.
		node = save_node(NULL, sh->tok, NULL, DEFAULT_ID);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return(node);
}

t_node	*parse_io_here(t_sh *sh)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	nod2 = NULL;
	if (sh->tok.tok == TOK_DLESS || sh->tok.tok == TOK_DLESSDASH)
	{
		node = save_node(NULL, sh->tok, NULL, DEFAULT_ID);
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		if ((nod2 = parse_here_end(sh)))
		{
			node = binnode(NULL, node, nod2);
			fifo_insert(sh->stack.here_docs, node);
		}
		else
			error_push(sh->stack.errors, PARSE_ERROR_NEAR, tok.data);
	}
	return(node);
}

t_node	*parse_here_end(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if (sh->tok.tok == TOK_WORD)
	{
		node = save_node(NULL, sh->tok, NULL, DEFAULT_ID);
		quote_removal(&(node->data));
		sh->tok = get_next_token(sh->input, sh->stack.errors);
	}
	return(node);
}

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
			sh->tok = get_next_token(sh->input, sh->stack.errors);
		}
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}

int		parse_linebreak(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;
	
	if (!lifo_empty(sh->stack.errors))
		return (0);
	node = NULL;
	if ((node = parse_newline_list(sh)))
		free(node);
	return (1);
}

t_node	*parse_separator_op(t_sh *sh)
{
	t_node		*node;
	t_tokens	tok;

	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	tok = sh->tok;
	if (tok.tok == TOK_AND || tok.tok == TOK_SEMI)
	{
		sh->tok = get_next_token(sh->input, sh->stack.errors);
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}

t_node	*parse_separator(t_sh *sh)
{
	t_node		*node;
	
	if (!lifo_empty(sh->stack.errors))
		return (NULL);
	node = NULL;
	if ((node = parse_separator_op(sh)))
		return (node);
	else if ((node = parse_newline_list(sh)))
		return (node);
	return (node);
}

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
