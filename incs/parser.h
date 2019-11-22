#ifndef PARSER_H
# define PARSER_H
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARGS_ARR_SIZE 4

enum			id {DEFAULT, ARGS, SUBSH, PIPESEQ, PIPE, ANDOR, IO_REDIRECT};
typedef	struct	s_flags
{
	unsigned	debug_all:1;
	unsigned	ast_draw:1;
}				t_flags;

typedef	struct		s_node
{
	struct s_node	*left;
	int				id; 
	char			**args;
	int				io;
	//voir si on remplacerai pas ca par une struct
	int				capacity;
	int				cur_size;
	int				cur_i;

	t_toktype		tok;
	char			*data;
	struct s_node	*right;
}					t_node;

t_flags		check_param(char **av);
void		bst_print_dot(t_node* tree, FILE* stream);

char		*push_args(t_node *node, char *s);

t_node		*binnode(t_node *left, t_node *mom, t_node *right);
t_node		*save_node(t_node *left, t_tokens tok, t_node *right, int id);
t_node		*applie_7b(t_tokens *cur, char *s);

/*
**	Parser function of BNF from opengroup POSIX SHELL documentation
*/
t_node		*parse_and_or(char *s, t_tokens *cur);
t_node		*parse_brace_group(char *s, t_tokens *cur);
t_node		*parse_case_clause(char *s, t_tokens *cur);
t_node		*parse_case_item(char *s, t_tokens *cur);
t_node		*parse_case_item_ns(char *s, t_tokens *cur);
t_node		*parse_case_list(char *s, t_tokens *cur);
t_node		*parse_case_list_ns(char *s, t_tokens *cur);
t_node		*parse_cmd_name(char *s, t_tokens *cur);
t_node		*parse_cmd_suffix(char *s, t_tokens *cur);
t_node		*parse_cmd_prefix(char *s, t_tokens *cur);
t_node		*parse_cmd_word(char *s, t_tokens *cur);
t_node		*parse_command(char *s, t_tokens *cur);
t_node		*parse_complete_command(char *s, t_tokens *cur);
t_node		*parse_complete_commands(char *s, t_tokens *cur);
t_node		*parse_compound_command(char *s, t_tokens *cur);
t_node		*parse_compound_list(char *s, t_tokens *cur);
t_node		*parse_do_group(char *s, t_tokens *cur);
t_node		*parse_else_part(char *s, t_tokens *cur);
t_node		*parse_filename(char *s, t_tokens *cur);
t_node		*parse_fname(char *s, t_tokens *cur);
t_node		*parse_for_clause(char *s, t_tokens *cur);
t_node		*parse_function_body(char *s, t_tokens *cur);
t_node		*parse_function_definition(char *s, t_tokens *cur);
t_node		*parse_here_end(char *s, t_tokens *cur);
t_node		*parse_if_clause(char *s, t_tokens *cur);
t_node		*parse_in(char *s, t_tokens *cur);
t_node		*parse_io_file(char *s, t_tokens *cur);
t_node		*parse_io_here(char *s, t_tokens *cur);
t_node		*parse_io_redirect(char *s, t_tokens *cur);
t_node		*parse_linebreak(char *s, t_tokens *cur);
t_node		*parse_list(char *s, t_tokens *cur);
t_node		*parse_name(char *s, t_tokens *cur);
t_node		*parse_newline_list(char *s, t_tokens *cur);
t_node		*parse_pattern(char *s, t_tokens *cur);
t_node		*parse_pipe_sequence(char *s, t_tokens *cur);
t_node		*parse_pipeline(char *s, t_tokens *cur);
t_node		*parse_program(char *s, t_tokens *cur);
t_node		*parse_redirect_list(char *s, t_tokens *cur);
t_node		*parse_separator(char *s, t_tokens *cur);
t_node		*parse_separator_op(char *s, t_tokens *cur);
t_node		*parse_sequential_sep(char *s, t_tokens *cur);
t_node		*parse_simple_command(char *s, t_tokens *cur);
t_node		*parse_subshell(char *s, t_tokens *cur);
t_node		*parse_term(char *s, t_tokens *cur);
t_node		*parse_until_clause(char *s, t_tokens *cur);
t_node		*parse_while_clause(char *s, t_tokens *cur);
t_node		*parse_wordlist(char *s, t_tokens *cur);
#endif
