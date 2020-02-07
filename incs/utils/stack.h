/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:25 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 18:35:25 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H
# include <stdlib.h>

enum	e_state_error{
	EMPTY,
	MATCH_LEX,
	UNEXPECTED_EOF,
	UNEXPECTED_TOKEN,
	UNRECOGNIZED_TOKEN,
	PARSE_ERROR
};

typedef struct	s_lifo
{
	int			top;
	void		*ar;
	int			capacity;
}				t_lifo;

typedef struct	s_fifo
{
	int			front;
	int			rear;
	void		**ar;
	int			capacity;
}				t_fifo;

typedef	struct	s_stacks
{
	t_lifo		*errors;
	t_fifo		*here_docs;
}				t_stacks;

typedef struct	s_staterror
{
	int			type;
	char		*near;
}				t_staterror;

/*
**	Lifo stack (realloc)
*/
t_lifo			*lifo_creator(unsigned capacity, size_t size);
int				lifo_full(t_lifo *stack);
int				lifo_empty(t_lifo *stack);
int				lifo_push(t_lifo *stack, int item);
int				lifo_pop(t_lifo *stack);
int				lifo_peek(t_lifo *stack);

/*
**	Fifo queue (no realloc)
*/
t_fifo			*fifo_creator(unsigned capacity, size_t size);
int				fifo_insert(t_fifo *q, void *item);
void			fifo_delete(t_fifo *q);
int				fifo_empty(t_fifo *q);
int				fifo_full(t_fifo *q);
void			*fifo_peek(t_fifo *q);
#endif
