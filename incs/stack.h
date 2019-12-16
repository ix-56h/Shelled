#ifndef FT_STACK_H
# define FT_STACK_H
#include <stdlib.h>

enum	e_state_error{
	EMPTY,
	UNCLOSED_SEQUENCE,
	UNRECOGNIZED_CHAR,
	UNRECOGNIZED_TOKEN,
	PARSE_ERROR_NEAR
};

typedef struct		s_int_stack
{
	int			top;
	int			*ar;
	unsigned	capacity;
}				t_int_stack;

t_int_stack		*int_stack_creator(unsigned capacity);
int				is_int_full(t_int_stack *stack);
int				is_int_empty(t_int_stack *stack);
int				int_push(t_int_stack *stack, int item);
int				int_pop(t_int_stack *stack);
int				int_peek(t_int_stack *stack);
#endif
