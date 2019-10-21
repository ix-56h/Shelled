/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 03:19:47 by niguinti          #+#    #+#             */
/*   Updated: 2019/07/30 18:30:42 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strcdup(const char *s1, char c)
{
	size_t	len;
	size_t	i;
	char	*dst;

	i = 0;
	len = ft_strclen(s1, c);
	if (!(dst = ft_strnew(len)))
		return (NULL);
	while (i != len && s1[i] != c)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
