/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:39 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/19 06:34:41 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void deleteTree(t_node* node) 
{
	int		i;

	i= 0;
	if (node == NULL)
		return;
	/* first delete both subtrees */
	deleteTree(node->left); 
	deleteTree(node->right); 

	/* then delete the node */
	if (node->id == ARGS)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->data != NULL)
		free(node->data);
	node->args = NULL;
	free(node);
	node = NULL;
} 

/* Deletes a tree and sets the root as NULL */
void delete_ast(t_node **root) 
{ 
	deleteTree(*root);
	*root = NULL;
}
