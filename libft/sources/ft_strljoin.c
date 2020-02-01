/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:39:31 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/01 04:46:55 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*ft_dupandfree(char *s1, char *s2, char to_free)
{
	char *tmp;

	if (!s1 && s2)
	{
		tmp = ft_strdup(s2);
		if (to_free & SECOND)
			free(s2);
		return (tmp);
	}
	else
	{
		tmp = ft_strdup(s1);
		if (to_free & FIRST)
			free(s1);
		return (tmp);
	}
}

/*
**	Join `s1' at the end of `s2'.
**	The fonciton will free `s1' or `s2' according to `to_free' with:
**	`NONE', `FIRST', `SECOND' or `BOTH'
**	Return the new malloced string
*/

char			*ft_strljoin(char *s1, char *s2, char to_free)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_dupandfree(s1, s2, to_free));
	else if (s1 && !s2)
		return (ft_dupandfree(s1, s2, to_free));
	i = 0;
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	if (to_free & FIRST)
		free(s1);
	if (to_free & SECOND)
		free(s2);
	return (str);
}
