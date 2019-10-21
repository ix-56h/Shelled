/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:39:48 by niguinti          #+#    #+#             */
/*   Updated: 2019/06/20 00:40:31 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*s)
	{
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
		if (*s && s++)
			len++;
	}
	return (len);
}
