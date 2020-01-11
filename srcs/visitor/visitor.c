/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/10 17:04:29 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <visitor_rules.h>

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
	/*
	** Function for 42sh
	*/
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
	/*
	** Function for 42sh
	*/
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

int		visit_dgreat(t_node *node)
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

int		visit_left_redi(t_node *node)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_right_redi(t_node *node)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_lessand(t_node *node)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_greatand(t_node *node)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_semi(t_node *node)
{
	return (visit(node->left) + visit(node->right));
}

int		visit_lessgreat(t_node *node)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit(t_node *root)
{
	if (!root)
		return (1);
	if (G_VISIT_RULES[root->tok])
	{
		if ((*G_VISIT_RULES[root->tok])(root))
		{
			printf("wahouh\n");
			return (1);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}
