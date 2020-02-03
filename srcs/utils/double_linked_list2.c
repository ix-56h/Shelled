/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 04:11:06 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 04:59:23 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "double_linked_list.h"

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
