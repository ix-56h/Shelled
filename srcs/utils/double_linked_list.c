/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:27:25 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/02 23:08:49 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "double_linked_list.h"

/*
**  Add a new node on the beggining of a list
**  Return 0 if succes and -1 if error
*/

int		dl_push(t_dl_node** head_ref, void *new_data) 
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

int		dl_append(t_dl_node** head_ref, void *new_data)
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

int     dl_push_node(t_dl_node** head_ref, t_dl_node *new_node, void *new_data)
{
	new_node->data = new_data; 
	new_node->next = *head_ref; 
	new_node->prev = NULL; 
	if (*head_ref != NULL) 
		(*head_ref)->prev = new_node; 
	*head_ref = new_node;
    return (0);
}

int		dl_append_node(t_dl_node** head_ref, t_dl_node *new_node, void *new_data)
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

int		dl_insert_before(t_dl_node* head_ref, t_dl_node* next_dl_node, void *new_data) 
{
    t_dl_node	*new_node;

	if (next_dl_node == NULL)
		return (-1);
	if (!(new_node = calloc(sizeof(t_dl_node), sizeof(t_dl_node)))) //calloc pas garder
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

/*
**	Find a node white the same data's address than needle param
**	return the first node occurance find or NULL
*/

t_dl_node	*dl_find_data(t_dl_node *haystack, void *needle)
{
	t_dl_node	*tmp;
	t_dl_node	*result;

	tmp = haystack;
	result = NULL;
	while (tmp)
	{
		if (tmp->data == needle)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	return the last node from head
*/

t_dl_node	*dl_get_last(t_dl_node *head)
{
	t_dl_node	*res;
	t_dl_node	*tmp_node;
	
	res = NULL;
	tmp_node = head;
	while (tmp_node)
	{
		res = tmp_node;
		tmp_node = tmp_node->next;
	}
	return (res);
}

t_dl_node	*dl_get_head(t_dl_node *node)
{
	t_dl_node	*res;
	t_dl_node	*tmp_node;
	
	res = NULL;
	tmp_node = node;
	while (tmp_node)
	{
		res = tmp_node;
		tmp_node = tmp_node->prev;
	}
	return (res);
}

void	dl_del_one(t_dl_node *node)
{
	t_dl_node	*next;
	t_dl_node	*prev;

	if (node)
	{
		next = node->next;
		prev = node->prev;
		free(node);
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}
}

void	dl_del_one_with_data(t_dl_node *node, void (*free_fonc)())
{
	t_dl_node	*next;
	t_dl_node	*prev;

	if (node)
	{
		next = node->next;
		prev = node->prev;
		free_fonc(node->data);
		free(node);
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}
}

void	dl_free_list(t_dl_node *head)
{
	t_dl_node	*tmp;

	if (!head)
		return ;
	while (head->prev)
		head = head->prev;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	dl_free_with_data(t_dl_node *head, void (*free_fonc)())
{
	t_dl_node	*tmp;

	tmp = head;
	while (tmp)
	{
		free_fonc(tmp->data);
		tmp = tmp->next;
	}
	dl_free_list(head);
}
