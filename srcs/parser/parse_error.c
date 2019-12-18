#include "parser.h"
#include "error_handler.h"

void	 free_ast(void)
{

}

int		error_push(t_stack *stack, int type, int i)
{

	if (is_int_full(stack))
		return (0);//realloc
	++stack->top;
	((t_staterror*)stack->ar)[stack->top].pos = i;
	((t_staterror*)stack->ar)[stack->top].type = type;
	return (1);
}

void	parse_error(int type)
{
	if (type == 1)
		printf("error\n");
}

t_staterror		error_peek(t_stack *stack)
{
	return (((t_staterror*)stack->ar)[stack->top]);
}

void	print_stack_errors(t_stack *stack, t_tokens *cur, char *s)
{
	t_staterror err;

	err = error_peek(stack);
	printf("%s", G_ERROR_MSGS_PREFIX[err.type]);
	int_pop(stack);
}

/*
t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;

	node = NULL;
	if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		//if ((node = parse_compound_list(s, cur)))
		if ((node = parse_complete_commands(s, cur)))
		{
			if (cur->tok == TOK_RPAREN)
			{
				node->id = SUBSH;
				*cur = get_next_token(s);
			}
			else
			{
				printf("Error : subshell need to be closed\n");
				node = NULL;
			}
		}
	}
	return (node);
}

*/
