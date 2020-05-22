/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:46:40 by niguinti          #+#    #+#             */
/*   Updated: 2019/06/20 18:40:19 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char	*temp;
	size_t	i;

	i = -1;
	temp = dest;
	while (++i < len && src[i])
		dest[i] = src[i];
	while (i < len)
		dest[i++] = '\0';
	return (temp);
}
