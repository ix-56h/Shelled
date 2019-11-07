/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 02:56:03 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/21 18:31:48 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_flags		f;

t_node	*parse_program(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	if (parse_linebreak(s, cur))
	{
		if (node = parse_complete_command(s, cur))
		{
			if (parse_linebreak(s, cur))
				return (node);
		}
	}
	return (NULL);
}

t_node	*parse_complete_commands(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;

	if (node = parse_complete_commands(s, cur))
	{
		if (parse_newline_list(s, cur) && (nod2 = parse_complete_command(s, cur)))
		{
			if (node = binnode(node, nod2, NULL))
				return (node);
		}
		else
			printf("Error: newline list or complete command expected\n");
	}
	else if (node = parse_complete_command(s, cur))
		return (node);
	return (NULL);
}

t_node	*parse_complete_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	if (node = parse_list(s, cur))
	{
		if (nod2 = parse_separator_op(s, cur))
			if (node = binnode(node, nod2, NULL))
				return (node);
		else
			return (node);
	}
	else
		printf("Error when parsing complete_command\n");
	return (NULL);
}

t_node	*parse_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;

	if (node = parse_list(s, cur))
	{
		if (nod2 = parse_separator_op(s, cur))
		{
			if (node = binnode(node, nod2, parse_and_or(s, cur)))
					return (node);
		}
	}
	else if (node = parse_and_or(s, cur))
		return (node);
	printf("Error when parsing list\n");
	return (NULL);
}

t_node	*parse_and_or(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	if (node = parse_pipeline(s, cur))
		return (node);
	else if (node = parse_and_or(s, cur))
	{
		tok = *cur;
		if (tok.tok == TOK_AND_IF || tok.tok == TOK_OR_IF)
			cur = get_next_token(s);
		if (nod2 = parse_linebreak(s, cur))
		{
			if (node = binnode(node, tok, nod2))
			{
				if (nod2 = parse_pipeline(s, cur))
					if (node = binnode(node, nod2, NULL)return (node);
		}
	}
	printf("Error when parsing AND_OR\n");
	return (NULL);
}

t_node	*parse_pipeline(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	tok = *cur;
	if (tok.tok == TOK_BANG)
		cur = get_next_token(s);
	// a verifier pour le bang, je sais pas a quoi il sert
	if (node = binnode(save_node(tok), parse_pipe_sequence(s, cur), NULL)
		return (node);
	printf("Error when parsing pipeline\n");
	return (NULL);
}

t_node	*parse_pipe_sequence(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	if (node = parse_command(s, cur))
		return (node);
	else if (node = parse_pipe_sequence(s, cur))
	{
		tok = *cur;
		if (tok.tok == TOK_PIPE)
			cur = get_next_token(s);
		else
		{
			printf("Error when parsing pipe_sequence\n");
			return (NULL);
		}
		if (node = binnode(parse_linebreak(s, cur), tok, parse_command(s, cur))
			return (node);
	}
	printf("Error when parsing pipe_sequence\n");
	return (NULL);
}

t_node	*parse_command(char *s, t_tokens *cur)
{
	t_node		*node;

	if (node = parse_simple_command(s, cur))
		return (node);
	else if (node = parse_compound_command(s, cur))
	{
		if (node = binnode(node, parse_redirect_list(s, cur), NULL)
			return (node);
	}
	else if (node = parse_function_definition(s, cur))
		return (node);
	printf("Error when parsing command\n");
	return (NULL);
}

t_node	*parse_compound_command(char *s, t_tokens *cur)
{
	t_node		*node;

	if (node = parse_brace_group(s, cur))
		return (node);
	else if (node = parse_subshell(s, cur))
		return (node);
	else if (node = parse_for_clause(s, cur))
		return (node);
	else if (node = parse_case_clause())
		return (node);
	else if (node = parse_if_clause(s, cur))
		return (node);
	else if (node = parse_while_clause(s, cur))
		return (node);
	else if (node = parse_until_clause(s, cur))
		return (node);
	printf("Error when parsing compound_command\n");
	return (NULL);
}

t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	tok = *cur;
	if (tok.tok == TOK_LPAREN)
	{
		cur = get_next_token(s);
		if (node = parse_compound_list(s, cur))
		{
			tok = *cur;
			if (tok.tok == TOK_RPAREN)
			{
				cur = get_next_token(s);
				return (node);
			}
			else
				print("Error, rparen expected\n");
		}
	}
	print("Error, lparen expected\n");
	return (node);
}

t_node	*parse_compound_list(char *s, t_tokens *cur)
{
	t_node		*node;
	
	if (node = parse_linebreak(s, cur))
	{
		if (node = binnode(node, parse_term(s, cur), parse_separator(s, cur)))
			return (node);
	}
	printf("Error parsing compound_list\n");
	return (NULL);
}

t_node	*parse_term(char *s, t_tokens *cur)
{
	t_node		*node;
	
	if (node = parse_term(s, cur))
	{
		if (node = binnode(node, parse_separator(s, cur), parse_and_or(s, cur)))
			return (node);
	}
	else if (node = parse_and_or(s, cur))
		return (node);
	printf("Error parsing term\n");
	return (NULL);
}

t_node	*parse_for_clause(char *s, t_tokens *cur);

t_node	*parse_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	tok = *cur;
	if (tok.tok == TOK_NAME)
	{
		//	applie rule 5
		cur = get_next_token(s);
		return (save_node(tok));
	}
	printf("Error parsing name\n");
	return (NULL);
}

t_node	*parse_in(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	tok = *cur;
	if (tok.tok == TOK_IN)
	{
		//	applie rule 6
		cur = get_next_token(s);
		return (save_node(tok));
	}
	printf("Error parsing name\n");
	return (NULL);
}

t_node	*parse_word_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	tok = *cur;
	if (node = parse_wordlist(s, cur))
	{
		tok = *cur;
		if (tok.tok == TOK_WORD)
		{
			cur = get_next_token(s);
			node = binnode(node, save_node(tok), NULL);	
			return (node);
		}
	}
	else if (tok.tok == TOK_WORD)
	{
		cur = get_next_token(s);
		node = binnode(NULL, save_node(tok), NULL);	
		return (node);
	}
	printf("Error parsing word list\n");
	return (NULL);
}

t_node	*parse_case_clause(char *s, t_tokens *cur);

t_node	*parse_case_list_ns(char *s, t_tokens *cur)
{
	t_node		*node;
	
	if (node = parse_case_list(s, cur))
	{
		if (node = binnode(node, parse_case_item_ns(s, cur), NULL))
			return (node);
	}
	else if (node = parse_case_item_ns(s, cur))
		return (node);
	printf("Error parsing case list ns\n");
	return (NULL);
}

t_node	*parse_case_list(char *s, t_tokens *cur)
{
	t_node		*node;
	
	if (node = parse_case_list(s, cur))
	{
		if (node = binnode(node, parse_case_item(s, cur), NULL))
			return (node);
	}
	else if (node = parse_case_item(s, cur))
		return (node);
	printf("Error parsing case list\n");
	return (NULL);
}

t_node	*parse_case_item_ns(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	if (tok.tok == T_LPAREN)
	{
		cur = get_next_token(s);
		tok = *cur;
		if ((node = parse_pattern(s)) && tok.tok == TOK_RPAREN)
			if (parse_linebreak())
			else if (parse_compound_list())
	//			success
	tok = *cur;
	if (node = parse_pattern(s, cur) && tok.tok == TOK_RPAREN)
	{
		cur = get_next_token(s);
		if (parse_linebreak() || parse_compound_list())
	//		success
	//	error
		//	error
}

t_node	*parse_case_item(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_pattern() && tok.tok == TOK_RPAREN)
	//	eat()
	//	if ((parse_linebreak() || parse_compound_list()) && tok.tok == TOK_DSEMI)
	//		eat()
	//		if (parse_linebreak())
	//			success
	//	error
	//else if (tok.tok == T_LPAREN)
	//	eat()
	//	if (parse_pattern() && (parse_linebreak()
	//		|| parse_compound_list()) && tok.tok == TOK_DSEMI)
	//		eat()
	//		if (parse_linebreak())
	//			success
	//	error

}

t_node	*parse_pattern(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 4
	//else if (parse_pattern() && tok.tok == TOK_PIPE)
	//	eat()
	//	if (tok.tok == TOK_WORD)
	//		eat()
	//		success
	//		do NOT applie rule 5
	//error
}

t_node	*parse_if_clause(char *s, t_tokens *cur);

t_node	*parse_else_part(char *s, t_tokens *cur);

t_node	*parse_while_clause(char *s, t_tokens *cur);

t_node	*parse_until_clause(char *s, t_tokens *cur);

t_node	*parse_function_definition(char *s, t_tokens *cur);

t_node	*parse_function_body(char *s, t_tokens *cur);

t_node	*parse_fname(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_NAME)
	//	eat()
	//	success
	//	applie rule 8
	//error
}

t_node	*parse_brace_group(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_LBRACE)
	//	eat()
	//	if (parse_compound_list() && tok.tok == TOK_RBRACE)
	//		eat()
	//		success
	//error
}

t_node	*parse_do_group(char *s, t_tokens *cur);

t_node	*parse_simple_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;
	
	if (node = parse_cmd_prefix(s, cur))
	{
		if (node = binnode(node, parse_cmd_word(s, cur), NULL))
		{
			if (nod2 = parse_cmd_suffix(s, cur))
			{
				node->right = nod2;
			}
			return (node);
		}
	}
	else if (node = parse_cmd_name(s, cur))
	{
		if (node = binnode(node, parse_cmd_suffix(s, cur), cur))
			return (node);
	}
	return (NULL);
}

t_node	*parse_cmd_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 7.a
	//error
}

t_node	*parse_cmd_word(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 7.b
	//error
}

t_node	*parse_cmd_prefix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_io_redirect())
	//	success
	//else if (parse_cmd_prefix() && parse_io_redirect())
	//	success
	//else if (tok.tok == TOK_ASSIGNEMENT_WORD)
	//	eat()
	//	success
	//else if (parse_cmd_prefix() && tok.tok == TOK_ASSIGNEMENT_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_cmd_suffix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_io_redirect())
	//	success
	//else if (parse_cmd_suffix() && parse_io_redirect())
	//	success
	//else if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//else if (parse_cmd_prefix() && tok.tok == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_redirect_list(char *s, t_tokens *cur)
{
	t_node		*node;
	
	node = NULL;
	if (node = parse_io_redirect(s, cur))
	{
		while (node = save_node(node, parse_io_redirect(s, cur), NULL))
			;
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
		cur = get_next_token(s);
		if (node = parse_filename(s, cur))
			node = save_node(NULL, tok, node);
		else if (node = parse_io_here(s, cur))
			node = save_node(NULL, tok, node);
	}
	else if (node = parse_filename(s, cur))
		return (node);
	else if (node = parse_io_here(s, cur))
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
		cur = get_next_token(s);
		if (node = parse_filename(s, cur))
			node = save_node(NULL, tok, node);
	}
	return (node);
}

t_node	*parse_filename(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	// rule 2
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_io_here(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_DLESS || tok.tok == TOK_DLESSDASH)
	{
		cur = get_next_token(s);
		if (node = parse_here_end(s, cur))
			node = save_node(NULL, tok, node);
	}
	return (node);
}

t_node	*parse_here_end(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	//rule 3
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//error
}

int		parse_newline_list(char *s, t_tokens *cur)
{
	int ret;

	ret = 0;
	while (cur->tok == NEWLINE)
	{
		ret = 1;
		cur = get_next_token(s);
	}
	return (ret);
}

int		parse_linebreak(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	if (parse_newline_list(s, cur))
		return (1);
	else if (!(*cur->data))
		return (1);
	return (0);
}

t_node	*parse_separator_op(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	tok = *cur;
	if (tok.tok == TOK_AND || tok.tok == TOK_SEMI)
	{
		cur = get_next_token(s);
		node = save_node(NULL, tok, NULL);
	}
	return (node);
}

t_node	*parse_separator(char *s, t_tokens *cur)
{
	t_node		*node;
	
	node = NULL;
	if (node = parse_separator_op(s, cur))
		return (node);
	else if (node = parse_newline_list(s, cur))
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
		cur = get_next_token(s);
		if (parse_linebreak(s, cur))
			node = save_node(NULL, tok, NULL);
	}
	else if (parse_newline_list())
		node = save_node(NULL, tok, NULL);
	return (node);
}

int main(int ac, char **av)
{
	char		*input = av[1];
	t_tokens	tok;
	t_node		*node = NULL;

	if (ac < 2)
	{
		printf("Usage: ./rdp \"ls -la > output.txt\" [-debug=all] [-ast=draw]\n");
		return (0);
	}
	f = check_param(av + 2);
	if (f.debug_all)
		printf("f.d = %u\nf.a = %u\n", f.debug_all, f.ast_draw);
	tok = get_next_token(input);
	//run the parser
	//node = expr(input, &tok);
	if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
	}
	return 0;
}
