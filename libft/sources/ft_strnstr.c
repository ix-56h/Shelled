/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:43:32 by niguinti          #+#    #+#             */
/*   Updated: 2019/06/01 02:41:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j]
				&& (j + i) < len)
			j++;
		if (!(needle[j]))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
