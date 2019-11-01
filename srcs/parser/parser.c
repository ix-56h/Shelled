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

void	parse_program(void)
{
	//if (parse_linebreak())
	//	if (parse_complete_command())
	//		if (parse_linebreak())
	//			success
	//		error
	//	success
}

void	parse_complete_commands(void)
{
	//if (parse_complete_commands())
	//	if (parse_newline_list())
	//		if (parse_complete_command())
	//			success;
	//else if (parse_complete_command())
	//	success;
	//error;
}

void	parse_complete_command(void)
{
	//if (parse_list())
	//	if (parse_separator_op())
	//		success;
	//	success;
	//error;
}

void	parse_list(void)
{
	//if (parse_list())
	//	if (parse_separator_op())
	//		if (parse_and_or())
	//			success
	//		error
	//	success
}

void	parse_and_or(void)
{
	//if (parse_pipeline())
	//	success 
	//else if (parse_and_or())
	//	if (token == TOK_AND_IF || token == TOK_OR_IF)
	//		eat();
	//		if (parse_linebreak() && parse_pipeline())
	//			success
	//	error
}

void	parse_pipeline(void)
{
	//if (parse_pipe_sequence())
	//	success
	//else if (token == TOK_BANG)
}

void	parse_pipe_sequence(void)
{
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

void	parse_command(void)
{
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

void	parse_compound_command(void)
{
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

void	parse_subshell(void)
{
	//if (token == TOK_LPAREN)
	//	eat()
	//	if (parse_compound_list() && token == TOK_RPAREN)
	//		eat()
	//		success
	//	error
	//error
}

void	parse_compound_list(void)
{
	//if (parse_linebreak() && parse_term())
	//	if (parse_separator())
	//		success
	//	success
	//error
}

void	parse_term(void)
{
	//	term	:	term seperator and_or
	//			|					and_or
	
	//if (parse_term() && parse_separator())
	//	success but not return 
	//if (parse_and_or())
	//	success return etc
	//error
}

void	parse_for_clause(void);

void	parse_name(void)
{
	//if (token == TOK_NAME)
	//	success
	//	applie rule 5
	//error
}

void	parse_in(void)
{
	//if (token == TOK_IN)
	//	success
	//	applie rule 6
	//error
}

void	parse_word_list(void)
{
	//if (parse_wordlist())
	//	if (token == TOK_WORD)
	//		eat()
	//		success
	//else if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

void	parse_case_clause(void);

void	parse_case_list_ns(void)
{
	//if (parse_case_list())
	//	if (parse_case_item_ns())
	//		success
	//else if (parse_case_item_ns())
	//	success
	//error
}

void	parse_case_list(void)
{
	//if (parse_case_list())
	//	if (parse_case_item())
	//		success
	//else if (parse_case_item())
	//	success
	//error
}

void	parse_case_item_ns(void)
{
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

void	parse_case_item(void)
{
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

void	parse_pattern(void)
{
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

void	parse_if_clause(void);

void	parse_else_part(void);

void	parse_while_clause(void);

void	parse_until_clause(void);

void	parse_function_definition(void);

void	parse_function_body(void);

void	parse_fname(void)
{
	//if (token == TOK_NAME)
	//	eat()
	//	success
	//	applie rule 8
	//error
}

void	parse_brace_group(void)
{
	//if (token == TOK_LBRACE)
	//	eat()
	//	if (parse_compound_list() && token == TOK_RBRACE)
	//		eat()
	//		success
	//error
}

void	parse_do_group(void);

void	parse_simple_command(void)
{
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

void	parse_cmd_name(void)
{
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 7.a
	//error
}

void	parse_cmd_word(void)
{
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//	applie rule 7.b
	//error
}

void	parse_cmd_prefix(void)
{
	//if (parse_io_redirect())
	//	success
	//else if (parse_cmd_prefix() && parse_io_redirect())
	//	success
	//else if (token == TOK_ASSIGN)
	//	eat()
	//	success
	//else if (parse_cmd_prefix() && token == TOK_ASSIGN)
	//	eat()
	//	success
	//error
}

void	parse_cmd_suffix(void)
{
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

void	parse_redirect_list(void)
{
	//if (parse_io_redirect())
	//	success
	//else if (parse_redirect_list() && parse_io_redirect())
	//	success
	//error
}

void	parse_io_redirect(void)
{
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

void	parse_io_file(void)
{
	//if (token == TOK_LREDI || token == TOK_LESSAND || token == TOK_RREDI
	//	|| token == TOK_GREATAND || token == TOK_DGREAT || token == TOK_LESSGREAT
	//	|| token == TOK_CLOBBER)
	//	eat()
	//	if (parse_filename())
	//		success
	//error
}

void	parse_filename(void)
{
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

void	parse_io_here(void)
{
	//if (token == TOK_DLESS || token == TOK_DLESSDASH)
	//	eat()
	//	if (parse_here_end())
	//		success
	//error
}

void	parse_here_end(void)
{
	//if (token == TOK_WORD)
	//	eat()
	//	success
	//error
}

void	parse_newline_list(void)
{
	//if (newline_list())
	//	success
	//if (token == NEWLINE)
	//	success
	//error;
}

void	parse_linebreak(void)
{
	//if (parse_newline_list())
	//	success;
	//else if (empty)
	//	success;
	//error;
}

void	parse_separator_op(void)
{
	//if (token == TOK_AND || token == TOK_SEMI)
	//	eat()
	//	success
	//error
}

void	parse_separator(void)
{
	//if (parse_separator_op() && parse_linebreak())
	//	success
	//else if (parse_newline_list())
	//	success
	//error
}

void	parse_sequential_sep(void)
{
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
