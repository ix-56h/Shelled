/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:56 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/14 00:44:03 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error_class.h"

int				error_push(t_lifo *stack, int type, char *near)
{
	if (lifo_full(stack))
		return (0);
	++stack->top;
	((t_staterror*)stack->ar)[stack->top].near = near;
	((t_staterror*)stack->ar)[stack->top].type = type;
	return (1);
}

t_staterror		error_peek(t_lifo *stack)
{
	return (((t_staterror*)stack->ar)[stack->top]);
}

void			print_stack_errors(t_lifo *stack, t_tokens *cur)
{
	t_staterror err;

	(void)cur;
	while (stack->top != -1)
	{
		err = error_peek(stack);
		ft_putstr(g_error_msgs_prefix[err.type]);
		if (err.near)
		{
			ft_putstr("'");
			ft_putstr(err.near);
			ft_putstr("'");
			if (err.type == UNRECOGNIZED_TOKEN)
				free(err.near);
		}
		ft_putstr("\n");
		stack->top--;
	}
}
