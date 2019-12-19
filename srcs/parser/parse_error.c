/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:56 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/19 06:34:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error_class.h"

void	 free_ast(void)
{

}

int		error_push(t_stack *stack, int type, char *near)
{
	if (is_int_full(stack))
		return (0);//realloc
	++stack->top;
	((t_staterror*)stack->ar)[stack->top].near = near;
	((t_staterror*)stack->ar)[stack->top].type = type;
	return (1);
}

t_staterror		error_peek(t_stack *stack)
{
	return (((t_staterror*)stack->ar)[stack->top]);
}

void	print_stack_errors(t_stack *stack, t_tokens *cur, char *s)
{
	t_staterror err;

	err = error_peek(stack);
	ft_putstr(G_ERROR_MSGS_PREFIX[err.type]);
	if (err.near != NULL)
	{
		ft_putstr("'");
		ft_putstr(err.near);
		ft_putstr("'");
	}
	ft_putstr("\n");
	int_pop(stack);
}

/*
t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;

	node = NULL;
	if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		//if ((node = parse_compound_list(s, cur)))
		if ((node = parse_complete_commands(s, cur)))
		{
			if (cur->tok == TOK_RPAREN)
			{
				node->id = SUBSH;
				*cur = get_next_token(s);
			}
			else
			{
				printf("Error : subshell need to be closed\n");
				node = NULL;
			}
		}
	}
	return (node);
}

*/
