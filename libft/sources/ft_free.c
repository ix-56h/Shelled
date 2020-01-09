/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:16:05 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/09 16:28:03 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
**  Free and return NULL
*/

void	*ft_free(void *alloced)
{
	if (alloced)
		free(alloced);
	return (NULL);
}
