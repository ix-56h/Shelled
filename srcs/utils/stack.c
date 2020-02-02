/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:35:55 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:18:01 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		return (0);
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
