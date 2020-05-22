/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:10:41 by mguerrea          #+#    #+#             */
/*   Updated: 2020/05/10 20:30:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "stdio.h"

void	add_jobnb(int nb)
{
	t_jobnb *jobnb;
	t_jobnb *new;

	jobnb = g_jobnb;
	new = (t_jobnb *)malloc(sizeof(t_jobnb));
	new->next = NULL;
	new->prev = NULL;
	new->number = nb;
	if (!jobnb)
		g_jobnb = new;
	else
	{
		while (jobnb->next)
			jobnb = jobnb->next;
		jobnb->next = new;
		new->prev = jobnb;
	}
}

void	del_jobnb(int nb)
{
	t_jobnb	*jobnb;
	t_jobnb	*tmp;

	jobnb = g_jobnb;
	while (jobnb && jobnb->number != nb)
		jobnb = jobnb->next;
	tmp = jobnb;
	if (tmp && tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	else if (tmp && !tmp->prev)
	{
		g_jobnb = tmp->next;
		if (g_jobnb)
			g_jobnb->prev = NULL;
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}

void	push_back(int nb)
{
	del_jobnb(nb);
	add_jobnb(nb);
}

void	push_front(int nb)
{
	t_jobnb *new;

	del_jobnb(nb);
	new = (t_jobnb *)malloc(sizeof(t_jobnb));
	new->number = nb;
	g_jobnb->prev = new;
	new->prev = NULL;
	new->next = g_jobnb;
	g_jobnb = new;
}
