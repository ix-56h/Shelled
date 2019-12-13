/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 02:56:03 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/08 15:44:39 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_flags		f;

t_node	*parse_program(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;

	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_complete_commands(s, cur)))
	{
		if ((nod2 = parse_linebreak(s, cur)))
			free(nod2);
		else if (cur->tok != TOK_EOF)
			node = NULL;
	}
	return (node);
}

t_node	*parse_complete_commands(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;

	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_complete_command(s, cur)))
	{
		while ((nod2 = parse_complete_command(s, cur)))
			node = binnode(node->left, node, nod2);
		if ((nod2 = parse_newline_list(s, cur)))
		{
			free(nod2);
			if ((nod2 = parse_complete_command(s, cur)))
				node = binnode(node, nod2, NULL);
			else
				node = NULL;
		}
	}
	return (node);
}

t_node	*parse_complete_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_list(s, cur)))
	{
		while ((nod2 = parse_list(s, cur)))
		{
			printf("while parselist here\n");
			node = binnode(node, nod2, nod2->right);
		}
		if ((nod2 = parse_separator_op(s, cur)))
			node = binnode(node, nod2, nod2->right);
	}
	return (node);
}

t_node	*parse_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_node		*nod3;

	(void)s;
	node = NULL;
	nod2 = NULL;
	nod3 = NULL;
	if ((node = parse_and_or(s, cur)))
	{
		while ((nod2 = parse_separator_op(s, cur)))
		{
			if ((nod3 = parse_and_or(s, cur)))
				node = binnode(node, nod2, nod3);
		}
	}
	return (node);
}

t_node	*parse_and_or(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_pipeline(s, cur)))
	{
		while ((nod2 = parse_pipeline(s, cur)))
			node = binnode(node->left, node, nod2);
		while ((tok = *cur).tok == TOK_AND_IF || tok.tok == TOK_OR_IF)
		{
			*cur = get_next_token(s);
			if ((nod2 = parse_pipeline(s, cur)))
				node = save_node(node, tok, nod2, 5);
			else
				node = NULL;
		}
	}
	return (node);
}

t_node	*parse_pipeline(char *s, t_tokens *cur)
{
	t_node		*node;

	(void)s;
	node = NULL;
	if (cur->tok == TOK_BANG)
	{
		if ((node = parse_pipe_sequence(s, cur)))
			node = save_node(node, *cur, NULL, 4);
		*cur = get_next_token(s);
	}
	else
		node = parse_pipe_sequence(s, cur);
	return (node);
}

t_node	*parse_pipe_sequence(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_command(s, cur)))
	{
		tok = *cur;
		while (tok.tok == TOK_PIPE)
		{
			*cur = get_next_token(s);
			if ((nod2 = parse_command(s, cur)))
				node = save_node(node, tok, nod2, 3);
			else
				node = NULL;
			tok = *cur;
		}
	}
	return (node);
}

t_node	*parse_command(char *s, t_tokens *cur)
{
	t_node	*node;
	t_node	*nod2;

	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_simple_command(s, cur)))
		return (node);
	else if ((node = parse_compound_command(s, cur)))
	{
		if ((nod2 = parse_redirect_list(s, cur)))
			node = binnode(node, nod2, nod2->right);
	}
	else
		node = parse_function_definition(s, cur);
	return (node);
}

t_node	*parse_compound_command(char *s, t_tokens *cur)
{
	t_node		*node;

	(void)s;
	node = NULL;
	if ((node = parse_brace_group(s, cur)))
		return (node);
	else if ((node = parse_subshell(s, cur)))
		return (node);
	else if ((node = parse_for_clause(s, cur)))
		return (node);
	else if ((node = parse_case_clause(s, cur)))
		return (node);
	else if ((node = parse_if_clause(s, cur)))
		return (node);
	else if ((node = parse_while_clause(s, cur)))
		return (node);
	else if ((node = parse_until_clause(s, cur)))
		return (node);
	return (node);
}

t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;

	(void)s;
	node = NULL;
	if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		if ((node = parse_compound_list(s, cur)))
		{
			if (cur->tok == TOK_RPAREN)
			{
				node->id = SUBSH;
				*cur = get_next_token(s);
			}
			else
			{
				printf("Error : subshell need to be closed\n");
				node = NULL;
			}
		}
	}
	return (node);
}

t_node	*parse_compound_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	(void)s;
	node = NULL;
	nod2 = NULL;

	if ((node = parse_term(s, cur)))
	{
		if ((nod2 = parse_separator(s, cur)))
			node = binnode(node, nod2, nod2->left);
	}
	return (node);
}

t_node	*parse_term(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	(void)s;
	node = NULL;
	nod2 = NULL;
	if ((node = parse_and_or(s, cur)))
	{
		// trouver une commande shell qui fait passer dans le while
		while ((nod2 = parse_and_or(s, cur)))
		{
			node = binnode(node, nod2, nod2->left);
		}
	}
	if (node && (nod2 = parse_separator(s, cur)))
	{
		node = binnode(node, nod2, nod2->right);
		if ((nod2 = parse_and_or(s, cur)))
			node = binnode(node->left, node, nod2);
	}
	return (node);
}

t_node	*parse_for_clause(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_name(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	(void)s;
	return (NULL);
}

t_node	*parse_in(char *s, t_tokens *cur)
{
	(void)s;
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_wordlist(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_case_clause(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_case_list_ns(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_case_list(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_case_item_ns(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_case_item(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_pattern(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_if_clause(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_else_part(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_while_clause(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_until_clause(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_function_definition(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_function_body(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_fname(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_brace_group(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_do_group(char *s, t_tokens *cur)
{
	(void)s;
	(void)cur;
	return (NULL);
}

t_node	*parse_simple_command(char *s, t_tokens *cur)
{
	t_node	*node;
	t_node	*nod2;
	t_node	*args;

	node = NULL;
	nod2 = NULL;

	if ((node = parse_cmd_prefix(s, cur)))
	{
		if (cur->tok == ASSIGNMENT_WORD && (nod2 = parse_cmd_word(s, cur)))
		{
			node = binnode(node->left, node, nod2);
			if ((nod2 = parse_cmd_suffix(s, cur)))
				node = binnode(node, nod2, nod2->right);
		}
	}
	else if ((node = parse_cmd_name(s, cur)))
	{
		args = node;
		while (cur->tok == TOK_WORD)
		{
			push_args(args, cur->data);
			//free
			*cur = get_next_token(s);
		}
		if ((nod2 = parse_cmd_suffix(s, cur)))
			node = binnode(node, nod2, nod2->left);
		while (cur->tok == TOK_WORD)
		{
			push_args(args, cur->data);
			//free
			*cur = get_next_token(s);
		}
	}
	return (node);
}

t_node	*parse_cmd_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	if (cur->tok == TOK_WORD)
	{
		if (!strchr(cur->data, '='))
		{
			applie_rule_one(s, cur);
			node = save_node(NULL, *cur, NULL, ARGS);
			*cur = get_next_token(s);
		}
		else
		{
			node = applie_7b(cur, cur->data);
			*cur = get_next_token(s);
		}
	}
	return(node);
}

t_node	*parse_cmd_word(char *s, t_tokens *cur)
{
	t_node		*node;
	char		*s2;

	s2 = cur->data;
	node = NULL;
	if (cur->tok == TOK_WORD)
	{
		node = applie_7b(cur, s2);
		*cur = get_next_token(s);
	}
	return(node);
}

t_node	*parse_cmd_prefix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	node = NULL;
	nod2 = NULL;
	tok = *cur;
	if (tok.tok == TOK_ASSIGNMENT_WORD)
	{
		node = save_node(NULL, tok, NULL, ASSIGNMENT_WORD);
		*cur = get_next_token(s);
		while ((tok = *cur).tok == TOK_ASSIGNMENT_WORD)
		{
			nod2 = save_node(NULL, tok, NULL, ASSIGNMENT_WORD);
			node = binnode(node, nod2, NULL);
			*cur = get_next_token(s);
		}
	}
	else if ((nod2 = parse_io_redirect(s, cur)))
	{
		return (nod2);
	}
	else
		return (NULL);
	return (node);
}

t_node	*parse_cmd_suffix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	node = NULL;
	nod2 = NULL;
	tok = *cur;
	if (tok.tok == TOK_WORD)
	{
		node = save_node(NULL, tok, NULL, ARGS);
		*cur = get_next_token(s);
		//while ((tok = *cur).tok == TOK_WORD)
		//{
		//	push_args(node, tok.data);
		//	*cur = get_next_token(s);
			//free
		//}
	}
	else if ((nod2 = parse_io_redirect(s, cur)))
		return (nod2);
	else
		return (NULL);
	return (node);
}

t_node	*parse_redirect_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	node = NULL;
	nod2 = NULL;
	if ((node = parse_io_redirect(s, cur)))
	{
		while ((nod2 = parse_io_redirect(s, cur)))
			node = binnode(nod2->left, nod2, node);
	}
	return (node);
}

t_node	*parse_io_redirect(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_IO_NUMBER)
	{
		*cur = get_next_token(s);
		if ((node = parse_io_file(s, cur))
			|| (node = parse_io_here(s, cur)))
		{
			node->io = ft_atoi(tok.data);
		}		
	}
	else if ((node = parse_io_file(s, cur))
			|| (node = parse_io_here(s, cur)))
		return (node);
	return (node);
}

t_node	*parse_io_file(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_LREDI || tok.tok == TOK_LESSAND || tok.tok == TOK_RREDI
		|| tok.tok == TOK_GREATAND || tok.tok == TOK_DGREAT || tok.tok == TOK_LESSGREAT
		|| tok.tok == TOK_CLOBBER)
	{
		*cur = get_next_token(s);
		if ((node = parse_filename(s, cur)))
			node = save_node(node, tok, NULL, IO_REDIRECT);
	}
	return (node);
}

t_node	*parse_filename(char *s, t_tokens *cur)
{
	t_node		*node;
	//t_node		*nod2;
	//t_node		*first;
	t_tokens	tok;

	node = NULL;
	//first = NULL;
	//nod2 = NULL;
	tok = *cur;
	// rule 2
	if (tok.tok == TOK_WORD)
	{
		node = save_node(NULL, *cur, NULL, DEFAULT_ID);
		//first = node;
		*cur = get_next_token(s);
		//while ((tok = *cur).tok == TOK_WORD)
		//{
		//	nod2 = save_node(NULL, *cur, NULL, DEFAULT_ID);
		//	binnode(nod2, node, NULL);
		//	node = nod2;
		//	*cur = get_next_token(s);
		//}
		//node = first;
	}
	return(node);
}

t_node	*parse_io_here(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;
	
	node = NULL;
	nod2 = NULL;
	if (cur->tok == TOK_DLESS || cur->tok == TOK_DLESSDASH)
	{
		node = save_node(NULL, *cur, NULL, DEFAULT_ID);
		*cur = get_next_token(s);
		if ((nod2 = parse_here_end(s, cur)))
			node = binnode(nod2, node, NULL);
	}
	return(node);
}

t_node	*parse_here_end(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	// rule 3  -> applie quote removal for get the true delimiter
	if (cur->tok == TOK_WORD)
	{
		node = save_node(NULL, *cur, NULL, DEFAULT_ID);
		*cur = get_next_token(s);
	}
	return(node);
}

t_node	*parse_newline_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	if (cur->tok == TOK_NEWLINE)
	{
		while (cur->tok == TOK_NEWLINE)
		{
			tok = *cur;
			*cur = get_next_token(s);
		}
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}

t_node	*parse_linebreak(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	if (cur->tok == TOK_NEWLINE)
		node = parse_newline_list(s, cur);
	else if (cur->tok == TOK_EOF)
		node = save_node(NULL, *cur, NULL, 0);
	return (node);
}

t_node	*parse_separator_op(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_AND || tok.tok == TOK_SEMI)
	{
		*cur = get_next_token(s);
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}

t_node	*parse_separator(char *s, t_tokens *cur)
{
	t_node		*node;
	
	node = NULL;
	if ((node = parse_separator_op(s, cur)))
		return (node);
	else if ((node = parse_newline_list(s, cur)))
		return (node);
	return (node);
}

t_node	*parse_sequential_sep(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_SEMI)
	{
		*cur = get_next_token(s);
		if ((node = parse_linebreak(s, cur)))
		{
			free(node);
			node = save_node(NULL, tok, NULL, 0);
		}
	}
	else if ((node = parse_newline_list(s, cur)))
	{
		free(node);
		node = save_node(NULL, tok, NULL, 0);
	}
	return (node);
}

int main(int ac, char **av)
{
	char		*input = av[1];
	t_tokens	tok;
	t_node		*node = NULL;

	if (ac < 2)
	{
		printf("Usage: ./21sh \"ls -la > output.txt\" [-debug=all] [-ast=draw]\n");
		return (0);
	}
	f = check_param(av + 2);
	if (f.debug_all)
		printf("f.d = %u\nf.a = %u\n", f.debug_all, f.ast_draw);
	tok = get_next_token(input);
	if (tok.tok == TOK_ERROR)
		return (0);
	//run the parser
	node = parse_program(input, &tok);
	if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
	}
	return 0;
}
