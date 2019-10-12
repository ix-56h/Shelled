#include "../includes/ast.h"
#include <stdlib.h>
#include <stdio.h>

t_astnode	*ast_create_node(t_tokens	*token)
{
	t_astnode	*new;
	
	if (!token)
		exit(0);
	if (!(new = malloc(sizeof(t_astnode))))
		exit(0);
	new->token = token->tok;
	new->literal = token->tok_literal;
	new->l = NULL;
	new->r = NULL;
	return (new);
}

t_astnode	*lex_tokens(t_tokens *tok_list)
{
	t_state		current_state;
	t_state		prev_state;
	t_tokens	*begin;
	t_astnode	*node;
	t_astnode	*new_node;
	begin = tok_list;
	while ((current_state = GET_STATE[tok_list->tok]))
	{
		if (new_node)
		{
			node = new_node;
			new_node = ast_create_node(tok_list);
			new_node->l = node;
		}
		else
			new_node = ast_create_node(tok_list);
		tok_list = tok_list->next;
	}
	return (new_node);
}

int	main(int ac, char **av)
{
	t_tokens	*tok_list = NULL;
	t_astnode		*ast = NULL;
	if (!(tok_list = tokenizer(av[1])))
	{
		printf("Error: Cant tokenize the string.\n");
		return (0);
	}
	ast = lex_tokens(tok_list);
	return (0);
}
