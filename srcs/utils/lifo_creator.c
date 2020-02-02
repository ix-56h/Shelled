/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifo_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:12:45 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:18:39 by niguinti         ###   ########.fr       */
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
