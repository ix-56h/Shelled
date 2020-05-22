/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 05:50:23 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:09:02 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*insert_str(char *s, size_t *pos, size_t anchor, char *str)
{
	char	*nw;
	size_t	i;

	i = 0;
	nw = NULL;
	if (!(nw = malloc(1 * ((ft_strlen(s) + ft_strlen(str)) - anchor))))
		return (NULL);
	while (i != *pos)
	{
		nw[i] = s[i];
		i++;
	}
	while (*str)
	{
		nw[i] = *str;
		str++;
		i++;
	}
	while (s[anchor])
	{
		nw[i] = s[anchor];
		i++;
		anchor++;
	}
	return (nw);
}
