/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:56 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 11:58:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error_class.h"

int		error_push(t_lifo *stack, int type, char *near)
{
	if (lifo_full(stack))
		return (0);//realloc
	++stack->top;
	((t_staterror*)stack->ar)[stack->top].near = near;
	((t_staterror*)stack->ar)[stack->top].type = type;
	return (1);
}

t_staterror		error_peek(t_lifo *stack)
{
	return (((t_staterror*)stack->ar)[stack->top]);
}

void	print_stack_errors(t_lifo *stack, t_tokens *cur, char *s)
{
	t_staterror err;
	(void)cur;
	(void)s;

	while (stack->top != -1)
	{
		err = error_peek(stack);
		ft_putstr(G_ERROR_MSGS_PREFIX[err.type]);
		if (err.near != NULL)
		{
			ft_putstr("'");
			ft_putstr(err.near);
			ft_putstr("'");
		}
		ft_putstr("\n");
		lifo_pop(stack);
	}
}
