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
	//	eat();
	//	if (parse_complete_command())
	//		eat();
	//		if (token == linebreak)
	//			parse_linebreak();
	//	else if (EOF)
	//		its just linebreak
	//	else
	//		error;
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

void	parse_linebreak(void)
{
	//if (parse_newline_list())
	//	success;
	//else if (empty)
	//	success;
	//error;
}

void	parse_newline_list(void)
{
	//if (newline_list())
	//	success
	//if (token == NEWLINE)
	//	success
	//error;
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
