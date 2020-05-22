/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:03:01 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/19 18:15:26 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && n--)
	{
		if (!*s1 && !*s2)
			return (0);
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (!n)
		return ((unsigned char)*--s1 - (unsigned char)*--s2);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
