/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 03:46:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/01 04:48:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
**  Replace the first occurence of `to_find' by `replace_str' in `str'
**  Return a fresh malloced string or `str' if `to_find' isn't found
*/

char	*ft_strreplace(char *str, char *to_find, char *replace_str)
{
	char	*head;
	char	*finded;
	char	*res;

	head = str;
	finded = str;
	if ((finded = ft_strstr(finded, to_find)))
	{
		res = ft_calloc(sizeof(char) * \
		(ft_strlen(head) + ft_strlen(replace_str) - ft_strlen(to_find) + 1));
		ft_strcpy(res, head);
		ft_memcpy(&res[finded - head + ft_strlen(replace_str)], \
			&res[finded - head + ft_strlen(to_find)], \
			ft_strlen(&res[finded - head + ft_strlen(to_find)]));
		ft_memcpy(&res[finded - head], replace_str, ft_strlen(replace_str));
		free(head);
		return (res);
	}
	return (head);
}
