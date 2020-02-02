/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:16:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/02 18:30:08 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "historique.h"
#include "double_linked_list.h"

int					historic_on_use(int act)
{
	static int on_use;

	if (act == 1)
		on_use = 1;
	else if (act == 2)
		on_use = 0;
	return (on_use);
}

t_historic			**get_historic()
{
    static t_historic *historic = NULL;

    return (&historic);
}

void				add_historic(t_dl_node *command)
{
    t_historic **historic;

    historic = get_historic();
    dl_push(historic, command);
}


t_historic				*controller_next(t_historic **historic)
{
	if ((*historic)->next)
	{
		*historic = (*historic)->next;
		historic_on_use(1);
		return(*historic);
	}
	else
		return (NULL);
}

t_historic				*controller_prev(t_historic **historic, t_historic *null_node)
{
	if ((*historic)->prev)
	{
		*historic = (*historic)->prev;
		historic_on_use(1);
		return(*historic);
	}
	else
	{
		if (*historic != null_node)
			*historic = null_node;
		return (NULL);
	}
}

t_historic				*controller_reset(t_historic **historic, t_historic **null_node)
{
	if (*null_node)
    	free(*null_node);
    *null_node = NULL;
    *historic = NULL;
	historic_on_use(1);
	return(*historic);
}

t_historic			*historic_controller(char act)
{
    static t_historic *historic = NULL;
    static t_historic *null_node = NULL;

	if (!historic)
		historic = *get_historic();
	if (historic)
	{
		if (!null_node)
		{
			null_node = ft_calloc(sizeof(t_historic));
        	null_node->next = historic;
			historic = null_node;
		}
		if (act == 0)
			return (controller_next(&historic));
		else if (act == 1)
			return (controller_prev(&historic, null_node));
		else if (act == 2)
			return (controller_reset(&historic, &null_node));
	}
    return (NULL);
}

t_dl_node				*historic_get_next(void)
{
    t_historic *node;

    node = historic_controller(0);
    if (node)
        return (node->data);
    return (NULL);
}

t_dl_node				*historic_get_last(void)
{
    t_historic *node;

    node = historic_controller(1);
    if (node)
        return (node->data);
    return (NULL);
}

void				historic_reset(void)
{
    historic_controller(2);
	historic_on_use(2);
}


void				free_historic()
{
	t_historic	*head;
	t_dl_node		*tmp;

	head = *get_historic();
	tmp = head;
	while (tmp)
	{
		dl_free_whith_content(tmp->data, free_line);
		tmp = tmp->next;
	}
	dl_free_list(head);
}
