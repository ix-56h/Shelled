/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:06:21 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/23 07:03:02 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "visitor.h"
#include "visitor_rules.h"

int		visit_cmd(t_node *node)
{
	if (node->tok == TOK_WORD)
	{
		printf("Executing : %s\n", node->data);
		return (1);
	}
	return (0);
}

int		visit_and_if(t_node *node)
{
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right))
				return (1);
		}
	}
	return (0);
}

int		visit_or_if(t_node *node)
{
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left))
				return (1);
		else if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right))
			return (1);
	}
	return (0);
}

int		visit_pipe(t_node *node)
{
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right))
				return (1);
		}
	}
	return (0);
}

int		visit_dless(t_node *node)
{
	return (0);
}

int		visit_dgreat(t_node *node)
{
	return (0);
}

int		visit_lessand(t_node *node)
{
	return (0);
}

int		visit_greatand(t_node *node)
{
	return (0);
}

int		visit_lessgreat(t_node *node)
{
	return (0);
}

int		visit_left_redi(t_node *node)
{
	return (0);
}

int		visit_right_redi(t_node *node)
{
	return (0);
}

int		visit_semi(t_node *node)
{
	return (0);
}

int		visit(t_node *root)
{
	if (!root)
		return (1);
	if (G_VISIT_RULES[root->tok] && (*G_VISIT_RULES[root->tok])(root))
	{
		printf("wahouh\n");
		return (1);
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}

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
	else
	{
		visit(node);
	}
	if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
	}

	free_sh(node, tok, stack);
	return (EXIT_SUCCESS);
}
