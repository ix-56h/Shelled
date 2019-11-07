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
}

t_node	*parse_complete_commands(char *s, t_tokens *cur)
{
}

t_node	*parse_complete_command(char *s, t_tokens *cur)
{
}

t_node	*parse_list(char *s, t_tokens *cur)
{
}

t_node	*parse_and_or(char *s, t_tokens *cur)
{
}

t_node	*parse_pipeline(char *s, t_tokens *cur)
{
}

t_node	*parse_pipe_sequence(char *s, t_tokens *cur)
{
}

t_node	*parse_command(char *s, t_tokens *cur)
{
	
}

t_node	*parse_compound_command(char *s, t_tokens *cur)
{
	return (parse_brace_group(s, cur) || parse_subshell(s, cur)  || parse_for_clause(s, cur)
			|| parse_case_clause(s, cur) || parse_if_clause(s, cur) || parse_while_clause(s, cur)
			|| parse_until_clause(s, cur));
}

t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;

	node = NULL;
	if (cur->tok == TOK_LPAREN)
	{
		cur = get_next_token(s);
		if (node = parse_compound_list(s, cur))
		{
			if (cur->tok == TOK_RPAREN)
				node->id = SUBSH;
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
	
	node = NULL;
	nod2 = NULL;
	if (node = parse_linebreak(s, cur))
	{
		if (nod2 = parse_term(s, cur))
			node = binnode(node, nod2, NULL);
		if (nod2 && nod2 = parse_separator(s, cur))
			node = binnode(node, nod2, NULL);
	}
	return (node);
}

t_node	*parse_term(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	node = NULL;
	nod2 = NULL;
	if (node = parse_and_or(s, cur))
	{
		while (nod2 = parse_and_or(s, cur))
			node = binnode(node, nod2, NULL);
	}
	if (node = parse_separator(s, cur))
	{
		if (nod2 = parse_and_or(s, cur))
			node = binnode(node, nod2, NULL);
	}
	return (node);
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

t_node	*parse_in(char *s, t_tokens *cur);

t_node	*parse_wordlist(char *s, t_tokens *cur);

t_node	*parse_case_clause(char *s, t_tokens *cur);

t_node	*parse_case_list_ns(char *s, t_tokens *cur);

t_node	*parse_case_list(char *s, t_tokens *cur);

t_node	*parse_case_item_ns(char *s, t_tokens *cur);

t_node	*parse_case_item(char *s, t_tokens *cur);

t_node	*parse_pattern(char *s, t_tokens *cur);

t_node	*parse_if_clause(char *s, t_tokens *cur);

t_node	*parse_else_part(char *s, t_tokens *cur);

t_node	*parse_while_clause(char *s, t_tokens *cur);

t_node	*parse_until_clause(char *s, t_tokens *cur);

t_node	*parse_function_definition(char *s, t_tokens *cur);

t_node	*parse_function_body(char *s, t_tokens *cur);

t_node	*parse_fname(char *s, t_tokens *cur);

t_node	*parse_brace_group(char *s, t_tokens *cur);

t_node	*parse_do_group(char *s, t_tokens *cur);

t_node	*parse_simple_command(char *s, t_tokens *cur)
{
	t_node	*node;
	t_node	*nod2;
// je ne sais pas comment je dois faire c'te fonction de mort, si je dois save les noeuds ainsi ou faire un array, bref, nsm, c'auoi un assignment_word ?	
	node = NULL;
	nod2 = NULL;
	if (node = parse_cmd_prefix(s, cur))
	{
		if (nod2 = parse_cmd_word(s, cur))
			node = binnode(node, nod2, NULL);
		if (nod2 && nod2 = parse_cmd_suffix(s, cur))
			node->right = nod2;
	}
	else if (node = parse_cmd_name(s, cur))
	{
		if (nod2 = parse_cmd_suffix(s, cur))
			node = binnode(node, nod2);
	}
	return (node);
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
	t_node		*nod2;
	t_tokens	tok;
	//char		*argvs;

	node = NULL;
	nod2 = NULL:
	tok = *cur;
	if (tok.tok == TOK_ASSIGNEMENT_WORD)
	{
		while (tok.tok == TOK_ASSIGNEMENT_WORD)
		{
			cur = get_next_token(s);
			//ici faire un array et push a chaque word, un suffix correspond a un argv d'un cmd_name qui lui correspond a une commande (builtin/programme)
			node = save_node(NULL, tok, NULL);
			tok = *cur;
		}
	}
	if (nod2 = parse_io_redirect(s, cur))
		node = binnode(node, nod2, NULL);
	return (node);
}

t_node	*parse_cmd_suffix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;
	//char		*argvs;

	node = NULL;
	nod2 = NULL:
	tok = *cur;
	if (tok.tok == TOK_WORD)
	{
		while (tok.tok == TOK_WORD)
		{
			cur = get_next_token(s);
			//ici faire un array et push a chaque word, un suffix correspond a un argv d'un cmd_name qui lui correspond a une commande (builtin/programme)
			node = save_node(NULL, tok, NULL);
			tok = *cur;
		}
	}
	if (nod2 = parse_io_redirect(s, cur))
		node = binnode(node, nod2, NULL);
	return (node);
}

t_node	*parse_redirect_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	
	node = NULL;
	nod2 = NULL;
	if (node = parse_io_redirect(s, cur))
	{
		while (nod2 = parse_io_redirect(s, cur))
			node = binnode(nod2, node, NULL);
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
		if ((node = parse_io_file(s, cur))
			|| (node = parse_io_here(s, cur)))
			node = save_node(tok, node, NULL);
	}
	else if ((node = parse_io_file(s, cur))
			|| (node = parse_io_here(s, cur)))
	{
		node = save_node(NULL, node, NULL);	
	}
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
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_io_here(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_DLESS || tok.tok == TOK_DLESSDASH)
	//	eat()
	//	if (parse_here_end())
	//		success
	//error
}

t_node	*parse_here_end(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (tok.tok == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_newline_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	if (cur->tok == NEWLINE)
	{
		while (cur->tok == NEWLINE)
		{
			tok = *cur;
			cur = get_next_token(s);
		}
		node = save_node(NULL, tok, NULL);
	}
	return (node);
}

t_node	*parse_linebreak(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	
	node = NULL;
	if (node = parse_newline_list(s, cur))
		return (node);
	//else if (empty)
	//	success;
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
	else if (parse_newline_list(s, cur))
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
