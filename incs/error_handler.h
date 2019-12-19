#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
#include "stack.h"

/*
**	parse_error.c
*/
void		print_stack_errors(t_stack *stack, t_tokens *cur, char *s);
int			error_push(t_stack *stack, int type, char *near);
#endif
