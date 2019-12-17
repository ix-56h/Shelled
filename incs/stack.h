#ifndef FT_STACK_H
# define FT_STACK_H
#include <stdlib.h>

enum	e_state_error{
	EMPTY,
	UNEXPECTED_EOF,
	UNCLOSED_SEQUENCE,
	UNRECOGNIZED_CHAR,
	UNRECOGNIZED_TOKEN,
	PARSE_ERROR_NEAR
};

typedef struct		s_staterror
{
	int				type;
	int				line;
	int				anchor;
	char			character;
}					t_staterror;

typedef struct		s_stack
{
	int			top;
	void		*ar;
	unsigned	capacity;
}				t_stack;

t_stack			*stack_creator(unsigned capacity, size_t size);
int				is_int_full(t_stack *stack);
int				is_int_empty(t_stack *stack);
int				int_push(t_stack *stack, int item);
int				int_pop(t_stack *stack);
int				int_peek(t_stack *stack);
#endif
