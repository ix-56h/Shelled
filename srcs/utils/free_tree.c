/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:39 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 05:24:32 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	delete_tree(t_node *node)
{
	int		i;

	i = 0;
	if (node == NULL)
		return ;
	delete_tree(node->left);
	delete_tree(node->right);
	if (node->id == ARGS)
	{
		while (i < node->cur_size)
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	if (node->data != NULL)
	{
		free(node->data);
		node->data = NULL;
	}
	free(node);
	node = NULL;
}

void	delete_ast(t_node **root)
{
	delete_tree(*root);
	*root = NULL;
}
