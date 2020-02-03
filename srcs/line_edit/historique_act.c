/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique_act.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:29:38 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 01:02:57 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "historique.h"
#include "double_linked_list.h"

void		add_historic(t_dl_node *command)
{
	t_historic **historic;

	historic = get_historic();
	dl_push(historic, command);
}

t_dl_node	*historic_get_next(void)
{
	t_historic *node;

	node = historic_controller(0);
	if (node)
		return (node->data);
	return (NULL);
}

t_dl_node	*historic_get_last(void)
{
	t_historic *node;

	node = historic_controller(1);
	if (node)
		return (node->data);
	return (NULL);
}

void		historic_reset(void)
{
	historic_controller(2);
	historic_on_use(2);
}

void		free_historic(void)
{
	t_historic	*head;
	t_dl_node	*tmp;

	head = *get_historic();
	tmp = head;
	while (tmp)
	{
		dl_free_with_data(tmp->data, free_line);
		tmp = tmp->next;
	}
	dl_free_list(head);
}
