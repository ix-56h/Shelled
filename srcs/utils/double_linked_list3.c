/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 04:11:14 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/08 23:57:35 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "double_linked_list.h"

/*
**	Find a node white the same data's address than needle param
**	return the first node occurance find or NULL
*/

t_dl_node	*dl_find_data(t_dl_node *haystack, void *needle)
{
	t_dl_node	*tmp;

	tmp = haystack;
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
