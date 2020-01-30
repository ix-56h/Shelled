/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:35:55 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/13 14:46:11 by niguinti         ###   ########.fr       */
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

int		lifo_full(t_lifo *stack)
{
	return (stack->top == (stack->capacity - 1));
}

int		lifo_empty(t_lifo *stack)
{
	return (stack->top == -1);
}

int		lifo_push(t_lifo *stack, int item)
{
	if (lifo_full(stack))
		return (0);//realloc
	((int*)stack->ar)[++stack->top] = item;
	return (1);
}

int		lifo_pop(t_lifo *stack)
{
	if (lifo_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top--]);
}

int		lifo_peek(t_lifo *stack)
{
	if (lifo_empty(stack))
		return (0);
	return (((int*)stack->ar)[stack->top]);
}
