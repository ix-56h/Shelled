/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:43:02 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/23 14:16:04 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dst;

	len = ft_strlen(s1);
	i = 0;
	if (!(dst = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	return (dst);
}
