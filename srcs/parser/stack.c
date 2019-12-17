#include "parser.h"

/*
**	unsigned	capacity	: capacity for the stack
**	size_t		size		: sizeof() type of the stack array
*/
t_stack	*stack_creator(unsigned capacity, size_t size)
{
	t_stack *stack;
	
	if (!(stack = malloc(sizeof(t_stack))))
		return (NULL);
	if (!(stack->ar = malloc(capacity * size))) 
		return (NULL);
	stack->capacity = capacity;
	stack->top = -1;
	return (stack);
}

int			is_int_full(t_stack *stack)
{
	return (stack->top == (stack->capacity - 1));
}

int			is_int_empty(t_stack *stack)
{
	return (stack->top == -1);
}

int			int_push(t_stack *stack, int item)
{
	if (is_int_full(stack))
		return (0);//realloc
	((int*)stack->ar)[++stack->top] = item;
	return (1);
}

int			int_pop(t_stack *stack)
{
	if (is_int_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top--]);
}

int			int_peek(t_stack *stack)
{
	if (is_int_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top]);
}


