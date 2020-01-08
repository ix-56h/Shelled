/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:39:48 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/08 15:11:02 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (s)
	{
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
	}
	return (len);
}
