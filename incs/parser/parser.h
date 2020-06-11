/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:18 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 19:06:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ast.h"
# include "sh.h"
# include "tokenizer.h"
# include "stack.h"
# include "error_handler.h"

# include <string.h>
# include <stdlib.h>
# define ARGS_ARR_SIZE 4

enum		e_id
{
	DEFAULT_ID,
	ARGS,
	SUBSH,
	GRP,
	PIPESEQ,
	PIPE,
	ANDOR,
	IO_REDIRECT,
	ASSIGNMENT_WORD
};

char		*push_args(t_node *node, char *s);

t_node		*binnode(t_node *left, t_node *mom, t_node *right);
t_node		*save_node(t_node *left, t_tokens tok, t_node *right, int id);
t_node		*applie_7b(t_tokens *cur, char *s);

/*
**	Parser function of BNF from opengroup POSIX SHELL documentation
*/
t_node		*parse_and_or(t_sh *sh);
t_node		*parse_brace_group(t_sh *sh);
t_node		*parse_case_clause(t_sh *sh);
t_node		*parse_case_item(t_sh *sh);
t_node		*parse_case_item_ns(t_sh *sh);
t_node		*parse_case_list(t_sh *sh);
t_node		*parse_case_list_ns(t_sh *sh);
t_node		*parse_cmd_name(t_sh *sh);
t_node		*parse_cmd_suffix(t_sh *sh);
t_node		*parse_cmd_prefix(t_sh *sh);
t_node		*parse_cmd_word(t_sh *sh);
t_node		*parse_command(t_sh *sh);
t_node		*parse_complete_command(t_sh *sh);
t_node		*parse_complete_commands(t_sh *sh);
t_node		*parse_compound_command(t_sh *sh);
t_node		*parse_compound_list(t_sh *sh);
t_node		*parse_do_group(t_sh *sh);
t_node		*parse_else_part(t_sh *sh);
t_node		*parse_filename(t_sh *sh);
t_node		*parse_fname(t_sh *sh);
t_node		*parse_for_clause(t_sh *sh);
t_node		*parse_function_body(t_sh *sh);
t_node		*parse_function_definition(t_sh *sh);
t_node		*parse_here_end(t_sh *sh);
t_node		*parse_if_clause(t_sh *sh);
t_node		*parse_in(t_sh *sh);
t_node		*parse_io_file(t_sh *sh);
t_node		*parse_io_here(t_sh *sh);
t_node		*parse_io_redirect(t_sh *sh);
int			parse_linebreak(t_sh *sh);
t_node		*parse_list(t_sh *sh);
t_node		*parse_name(t_sh *sh);
t_node		*parse_newline_list(t_sh *sh);
t_node		*parse_pattern(t_sh *sh);
t_node		*parse_pipe_sequence(t_sh *sh);
t_node		*parse_pipeline(t_sh *sh);
t_node		*parse_program(t_sh *sh);
t_node		*parse_redirect_list(t_sh *sh);
t_node		*parse_separator(t_sh *sh);
t_node		*parse_separator_op(t_sh *sh);
t_node		*parse_sequential_sep(t_sh *sh);
t_node		*parse_simple_command(t_sh *sh);
t_node		*parse_subshell(t_sh *sh);
t_node		*parse_term(t_sh *sh);
t_node		*parse_until_clause(t_sh *sh);
t_node		*parse_while_clause(t_sh *sh);
t_node		*parse_wordlist(t_sh *sh);

/*
**	misc.c
*/
t_node		*push_node_left(t_node *to_push, t_node *branch);
t_node		*binnode(t_node *left, t_node *mom, t_node *right);
t_node		*save_node(t_node *left, t_tokens tok, t_node *right, int id);
void		applie_rule_one(char *s, t_tokens *cur);
t_node		*applie_7b(t_tokens *cur, char *s);

/*
**	free_tree.c
*/
void		delete_tree(t_node *node);
void		delete_ast(t_node **root);
#endif
