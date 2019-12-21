/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:25 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/20 00:42:09 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H
#include <stdlib.h>

enum	e_state_error{
	EMPTY,
	MATCH_LEX,
	UNEXPECTED_EOF,
	UNEXPECTED_TOKEN,
	UNRECOGNIZED_TOKEN,
	PARSE_ERROR_NEAR
};

typedef struct		s_staterror
{
	int				type;
	char			*near;
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