/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:23:58 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/04 19:49:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrimf(char *s)
{
	size_t			len;
	unsigned int	start;
	char			*ret;

	ret = NULL;
	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && (s[start] == '\n' || s[start] == ' '
			|| s[start] == '\t'))
		start++;
	len = ft_strlen(s);
	if (len > 0)
	{
		while ((s[len - 1] == '\n' || s[len - 1] == ' ' || s[len - 1] == '\t')
				&& len > start)
			len--;
		if (!(ret = ft_strsub(s, start, (len - start))))
			return (NULL);
		free(s);
	}
	return (ret);
}
