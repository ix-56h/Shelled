/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:32:39 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:12:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			fifo_insert(t_fifo *q, void *item)
{
	if (fifo_full(q))
		return (0);
	if (q->front == -1)
		q->front = 0;
	(q->ar)[++q->rear] = item;
	return (1);
}

void		fifo_delete(t_fifo *q)
{
	if (fifo_empty(q))
		return ;
	q->front = q->front + 1;
}

int			fifo_empty(t_fifo *q)
{
	return ((q->front == -1 || q->front == q->rear + 1) ? 1 : 0);
}

int			fifo_full(t_fifo *q)
{
	return ((q->front == q->capacity - 1) ? 1 : 0);
}

void		*fifo_peek(t_fifo *q)
{
	if (fifo_empty(q))
		return (NULL);
	return (q->ar[q->front]);
}
