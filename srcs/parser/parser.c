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

	//if (node = parse_linebreak(s, cur))
	//	if (node = parse_complete_command(s, cur))
	//		if (parse_linebreak(s, cur))
	//			return (node);
	//		return (NULL);
	//	return (node);
	//return (NULL);
}

t_node	*parse_complete_commands(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (node = parse_complete_commands())
	//	if (parse_newline_list())
	//		if (node = binode(node, tok, parse_complete_command()))
	//			return (node);
	//
	//error;
}

t_node	*parse_complete_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_list())
	//	if (parse_separator_op())
	//		success;
	//	success;
	//error;
}

t_node	*parse_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_list())
	//	if (parse_separator_op())
	//		if (parse_and_or())
	//			success
	//		error
	//	success
}

t_node	*parse_and_or(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_pipeline())
	//	success 
	//else if (parse_and_or())
	//	if (token == TOK_AND_IF || token == TOK_OR_IF)
	//		eat();
	//		if (parse_linebreak() && parse_pipeline())
	//			success
	//	error
}

t_node	*parse_pipeline(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_pipe_sequence())
	//	success
	//else if (token == TOK_BANG)
}

t_node	*parse_pipe_sequence(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_command())
	//	success
	//else if (parse_pipe_sequence())
	//	if (token == TOK_PIPE)
	//		eat()
	//		if (parse_linebreak() && parse_command())
	//			success
	//	error
	//error
}

t_node	*parse_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_simple_command())
	//	success
	//else if (parse_compound_command())
	//	if (parse_redirect_list())
	//		success
	//	success
	//else if (parse_function_definition())
	//	success
	//error
}

t_node	*parse_compound_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_brace_group())
	//	success
	//else if (parse_subshell())
	//	success
	//else if (parse_for_clause())
	//	success
	//else if (parse_case_clause())
	//	success
	//else if (parse_if_clause())
	//	success
	//else if (parse_while_clause())
	//	success
	//else if (parse_until_clause())
	//	success
	//error
}

t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_LPAREN)
	//	eat()
	//	if (parse_compound_list() && token == TOK_RPAREN)
	//		eat()
	//		success
	//	error
	//error
}

t_node	*parse_compound_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_linebreak() && parse_term())
	//	if (parse_separator())
	//		success
	//	success
	//error
}

t_node	*parse_term(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//	term	:	term seperator and_or
	//			|					and_or
	
	//if (parse_term() && parse_separator())
	//	success but not return 
	//if (parse_and_or())
	//	success return etc
	//error
}

t_node	*parse_for_clause(char *s, t_tokens *cur);

t_node	*parse_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_NAME)
	//	success
	//	applie rule 5
	//error
}

t_node	*parse_in(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_IN)
	//	success
	//	applie rule 6
	//error
}

t_node	*parse_word_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_wordlist())
	//	if (token == TOK_WORD)
	//		eat()
	//		success
	//else if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_case_clause(char *s, t_tokens *cur);

t_node	*parse_case_list_ns(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_case_list())
	//	if (parse_case_item_ns())
	//		success
	//else if (parse_case_item_ns())
	//	success
	//error
}

t_node	*parse_case_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_case_list())
	//	if (parse_case_item())
	//		success
	//else if (parse_case_item())
	//	success
	//error
}

t_node	*parse_case_item_ns(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_pattern() && token == TOK_RPAREN)
	//	eat()
	//	if (parse_linebreak() || parse_compound_list())
	//		success
	//	error
	//else if (token == T_LPAREN)
	//	eat()
	//	if (parse_pattern() && token == TOK_RPAREN)
	//		if (parse_linebreak() || parse_compound_list())
	//			success
	//	error
}

t_node	*parse_case_item(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_pattern() && token == TOK_RPAREN)
	//	eat()
	//	if ((parse_linebreak() || parse_compound_list()) && token == TOK_DSEMI)
	//		eat()
	//		if (parse_linebreak())
	//			success
	//	error
	//else if (token == T_LPAREN)
	//	eat()
	//	if (parse_pattern() && (parse_linebreak()
	//		|| parse_compound_list()) && token == TOK_DSEMI)
	//		eat()
	//		if (parse_linebreak())
	//			success
	//	error

}

t_node	*parse_pattern(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 4
	//else if (parse_pattern() && token == TOK_PIPE)
	//	eat()
	//	if (token == TOK_WORD)
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
	//if (token == TOK_NAME)
	//	eat()
	//	success
	//	applie rule 8
	//error
}

t_node	*parse_brace_group(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_LBRACE)
	//	eat()
	//	if (parse_compound_list() && token == TOK_RBRACE)
	//		eat()
	//		success
	//error
}

t_node	*parse_do_group(char *s, t_tokens *cur);

t_node	*parse_simple_command(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_cmd_prefix())
	//	if (parse_cmd_word())
	//		if (parse_cmd_suffix())
	//			success
	//		success
	//	success
	//else if (parse_cmd_name())
	//	if (parse_cmd_suffix())
	//		success
	//	success
	//error
}

t_node	*parse_cmd_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 7.a
	//error
}

t_node	*parse_cmd_word(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_WORD)
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
	//else if (token == TOK_ASSIGNEMENT_WORD)
	//	eat()
	//	success
	//else if (parse_cmd_prefix() && token == TOK_ASSIGNEMENT_WORD)
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
	//else if (token == TOK_WORD)
	//	eat()
	//	success
	//else if (parse_cmd_prefix() && token == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_redirect_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_io_redirect())
	//	success
	//else if (parse_redirect_list() && parse_io_redirect())
	//	success
	//error
}

t_node	*parse_io_redirect(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_io_file())
	//	success
	//else if (token == TOK_IO_NUMBER)
	//	eat()
	//	if (parse_io_file())
	//		success
	//else if (parse_io_here())
	//	success
	//else if (token == TOK_IO_NUMBER)
	//	eat()
	//	if (parse_io_here())
	//		success
	//error
}

t_node	*parse_io_file(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_LREDI || token == TOK_LESSAND || token == TOK_RREDI
	//	|| token == TOK_GREATAND || token == TOK_DGREAT || token == TOK_LESSGREAT
	//	|| token == TOK_CLOBBER)
	//	eat()
	//	if (parse_filename())
	//		success
	//error
}

t_node	*parse_filename(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_io_here(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_DLESS || token == TOK_DLESSDASH)
	//	eat()
	//	if (parse_here_end())
	//		success
	//error
}

t_node	*parse_here_end(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

t_node	*parse_newline_list(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (newline_list())
	//	success
	//if (token == NEWLINE)
	//	success
	//error;
}

t_node	*parse_linebreak(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_newline_list())
	//	success;
	//else if (empty)
	//	success;
	//error;
}

t_node	*parse_separator_op(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_AND || token == TOK_SEMI)
	//	eat()
	//	success
	//error
}

t_node	*parse_separator(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (parse_separator_op() && parse_linebreak())
	//	success
	//else if (parse_newline_list())
	//	success
	//error
}

t_node	*parse_sequential_sep(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;
	//if (token == TOK_SEMI)
	//	eat()
	//	if (parse_linebreak())
	//		success
	//else if (parse_newline_list())
	//	success
	//
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
