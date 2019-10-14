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

int	main(int ac, char **av)
{
	t_astnode		*ast = NULL;
	
	return (0);
}
