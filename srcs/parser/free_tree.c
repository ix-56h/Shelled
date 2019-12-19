/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 02:56:03 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/08 15:44:39 by thdelmas         ###   ########.fr       */
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
