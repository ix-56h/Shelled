#include "parser.h"

t_int_stack		*int_stack_creator(unsigned capacity)
{
	t_int_stack *stack;
	if (!(stack = malloc(sizeof(t_int_stack))))
		return (NULL);
	if (!(stack->ar = malloc(capacity * sizeof(*(stack->ar)))))
		return (NULL);
	stack->capacity = capacity;
	stack->top = -1;
	return (stack);
}

int			is_int_full(t_int_stack *stack)
{
	return (stack->top == (stack->capacity - 1));
}

int			is_int_empty(t_int_stack *stack)
{
	return (stack->top == -1);
}

int			int_push(t_int_stack *stack, int item)
{
	if (is_int_full(stack))
		return (0);//realloc
	stack->ar[++stack->top] = item;
	return (1);
}

int			int_pop(t_int_stack *stack)
{
	if (is_int_empty(stack))
		return (EMPTY);
	return (stack->ar[stack->top--]);
}

int			int_peek(t_int_stack *stack)
{
	if (is_int_empty(stack))
		return (EMPTY);
	return (stack->ar[stack->top]);
}
