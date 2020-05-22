/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:49:17 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/23 14:30:53 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	tmp;

	j = 0;
	tmp = ft_strlen(dst);
	i = tmp;
	if (size == 0)
		return (ft_strlen(src));
	while (src[j] && i < (size - 1))
	{
		dst[i] = src[j];
		++i;
		++j;
	}
	dst[i] = '\0';
	if (tmp < size)
		return (tmp + ft_strlen(src));
	return (size + ft_strlen(src));
}
