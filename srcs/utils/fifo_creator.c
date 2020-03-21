/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:12:45 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:16:02 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_fifo		*fifo_creator(unsigned capacity, size_t size)
{
	t_fifo *queue;

	if (!(queue = malloc(sizeof(t_fifo))))
		return (NULL);
	if (!(queue->ar = malloc(capacity * size)))
		return (NULL);
	queue->capacity = capacity;
	queue->front = -1;
	queue->rear = -1;
	return (queue);
}
