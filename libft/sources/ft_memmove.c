/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:23:26 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/19 18:14:32 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*cdst;
	const unsigned char	*csrc;

	i = 0;
	cdst = (unsigned char*)dst;
	csrc = (unsigned char*)src;
	if (cdst < csrc)
		while (i < len)
		{
			cdst[i] = csrc[i];
			i++;
		}
	else
	{
		i = len;
		while (i > 0)
		{
			cdst[i - 1] = csrc[i - 1];
			i--;
		}
	}
	return (dst);
}
