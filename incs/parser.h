#ifndef PARSER_H
# define PARSER_H
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef	struct	s_flags
{
	unsigned	debug_all:1;
	unsigned	ast_draw:1;
}				t_flags;

typedef	struct		s_node
{
	struct s_node	*left;
	enum			id (ARGS);
	char			**args;
	t_toktype		tok;
	char			*data;
	struct s_node	*right;
}					t_node;

t_flags	check_param(char **av);
void bst_print_dot(t_node* tree, FILE* stream);
#endif
