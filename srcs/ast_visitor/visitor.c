/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:06:21 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/23 03:59:19 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "visitor.h"

void	visit_cmd();
void	visit_or_if();
void	visit_and_if();
void	visit_dless();
void	visit_dgreat();
void	visit_lessand();
void	visit_greatand();
void	visit_lessgreat();
void	visit_dlessdash();

void	free_sh(t_node *node, t_tokens tok, t_stack *stack)
{
	if (node != NULL)
		delete_ast(&node);
	if (tok.data != NULL)
		free(tok.data);
	free(stack->ar);
	free(stack);
}


int main(int ac, char **av)
{
	char		*input = av[1];
	t_tokens	tok;
	t_node		*node = NULL;
	t_stack		*stack;
	t_flags		f;

	f.ast_draw = 0;
	if (!(stack = stack_creator(20, sizeof(t_staterror))))
		return (EXIT_FAILURE);
	if (ac < 2)
	{
		printf("Usage: ./21sh \"ls -la > output.txt\" [-ast=draw]\n");
		return (EXIT_FAILURE);
	}
	check_param(av + 2, &f);
	tok = get_next_token(input, stack);
	if (is_int_empty(stack))
		node = parse_program(input, &tok, stack);
	if (!is_int_empty(stack))
	{
		print_stack_errors(stack, &tok, input);
		free_sh(node, tok, stack);
		return (EXIT_FAILURE);
	}
	else if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
	}
	free_sh(node, tok, stack);
	return (EXIT_SUCCESS);
}
