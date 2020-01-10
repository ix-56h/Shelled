/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:25 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/10 14:21:41 by niguinti         ###   ########.fr       */
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

typedef struct	s_lifo
{
	int			top;
	void		*ar;
	unsigned	capacity;
}				t_lifo;

typedef	struct  s_stacks
{
	t_lifo		*errors;
//	t_fifo		*here_docs;
}				t_stacks;

typedef struct	s_staterror
{
	int			type;
	char		*near;
}				t_staterror;

t_lifo			*lifo_creator(unsigned capacity, size_t size);
int				is_int_full(t_lifo *stack);
int				is_int_empty(t_lifo *stack);
int				int_push(t_lifo *stack, int item);
int				int_pop(t_lifo *stack);
int				int_peek(t_lifo *stack);
#endif
