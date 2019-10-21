/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:42:19 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/23 14:04:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int j;
	int i;

	i = 0;
	if (!needle[i] && !haystack[i])
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!(needle[j]))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
