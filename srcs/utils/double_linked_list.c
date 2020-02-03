/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:27:25 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 04:59:16 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "double_linked_list.h"

/*
**  Add a new node on the beggining of a list
**  Return 0 if succes and -1 if error
*/

int		dl_push(t_dl_node **head_ref, void *new_data)
{
	t_dl_node	*new_node;

	if (!(new_node = malloc(sizeof(t_dl_node))))
		return (-1);
	new_node->data = new_data;
	new_node->next = *head_ref;
	new_node->prev = NULL;
	if (*head_ref != NULL)
		(*head_ref)->prev = new_node;
	*head_ref = new_node;
	return (0);
}

/*
**  Add a new node on the end of a list
**  Return 0 if succes and -1 if error
*/

int		dl_append(t_dl_node **head_ref, void *new_data)
{
	t_dl_node	*new_node;
	t_dl_node	*nav_node;

	nav_node = *head_ref;
	while (nav_node && nav_node->next)
		nav_node = nav_node->next;
	if (!(new_node = ft_calloc(sizeof(t_dl_node))))
		return (-1);
	new_node->data = new_data;
	if (nav_node)
	{
		nav_node->next = new_node;
		new_node->prev = nav_node;
	}
	else
		*head_ref = new_node;
	return (0);
}

int		dl_push_node(t_dl_node **head_ref, t_dl_node *new_node, void *new_data)
{
	new_node->data = new_data;
	new_node->next = *head_ref;
	new_node->prev = NULL;
	if (*head_ref != NULL)
		(*head_ref)->prev = new_node;
	*head_ref = new_node;
	return (0);
}

int		dl_append_node(t_dl_node **head_ref, t_dl_node *new_node\
		, void *new_data)
{
	t_dl_node	*nav_node;

	nav_node = *head_ref;
	while (nav_node && nav_node->next)
		nav_node = nav_node->next;
	if (!(new_node = ft_calloc(sizeof(t_dl_node))))
		return (-1);
	new_node->data = new_data;
	if (nav_node)
	{
		nav_node->next = new_node;
		new_node->prev = nav_node;
	}
	else
		*head_ref = new_node;
	return (0);
}

/*
**  Add a new node before 'next_dl_node'
**  Return 0 if succes and -1 if error
*/

int		dl_insert_before(t_dl_node *head_ref, t_dl_node *next_dl_node\
		, void *new_data)
{
	t_dl_node	*new_node;

	if (next_dl_node == NULL)
		return (-1);
	if (!(new_node = ft_calloc(sizeof(t_dl_node))))
		return (-1);
	new_node->data = new_data;
	new_node->prev = next_dl_node->prev;
	next_dl_node->prev = new_node;
	new_node->next = next_dl_node;
	if (new_node->prev != NULL)
		new_node->prev->next = new_node;
	else
		head_ref = new_node;
	return (0);
}
