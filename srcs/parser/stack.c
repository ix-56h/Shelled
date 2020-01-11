/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:35:55 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/10 16:54:53 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
**	unsigned	capacity	: capacity for the stack
**	size_t		size		: sizeof() type of the stack array
*/
t_lifo	*lifo_creator(unsigned capacity, size_t size)
{
	t_lifo *stack;
	
	if (!(stack = malloc(sizeof(t_lifo))))
		return (NULL);
	if (!(stack->ar = malloc(capacity * size))) 
		return (NULL);
	stack->capacity = capacity;
	stack->top = -1;
	return (stack);
}

int			is_int_full(t_lifo *stack)
{
	return (stack->top == (stack->capacity - 1));
}

int			is_int_empty(t_lifo *stack)
{
	return (stack->top == -1);
}

int			int_push(t_lifo *stack, int item)
{
	if (is_int_full(stack))
		return (0);//realloc
	((int*)stack->ar)[++stack->top] = item;
	return (1);
}

int			int_pop(t_lifo *stack)
{
	if (is_int_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top--]);
}

int			int_peek(t_lifo *stack)
{
	if (is_int_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top]);
}
