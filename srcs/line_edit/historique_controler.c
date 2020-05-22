/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique_controler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:26:11 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 01:03:52 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "historique.h"
#include "double_linked_list.h"

t_historic	*controller_next(t_historic **historic)
{
	if ((*historic)->next)
	{
		*historic = (*historic)->next;
		historic_on_use(1);
		return (*historic);
	}
	else
		return (NULL);
}

t_historic	*controller_prev(t_historic **historic, t_historic *null_node)
{
	if ((*historic)->prev)
	{
		*historic = (*historic)->prev;
		historic_on_use(1);
		return (*historic);
	}
	else
	{
		if (*historic != null_node)
			*historic = null_node;
		return (NULL);
	}
}

t_historic	*controller_reset(t_historic **historic, t_historic **null_node)
{
	if (*null_node)
		free(*null_node);
	*null_node = NULL;
	*historic = NULL;
	historic_on_use(1);
	return (*historic);
}

t_historic	*historic_controller(char act)
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
