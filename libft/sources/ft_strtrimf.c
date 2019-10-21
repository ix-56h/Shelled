/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:23:58 by niguinti          #+#    #+#             */
/*   Updated: 2019/08/10 13:24:31 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrimf(char *s)
{
	size_t			len;
	unsigned int	start;
	char			*ret;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == '\n' || s[start] == ' ' || s[start] == '\t')
		start++;
	len = ft_strlen(s);
	while ((s[len - 1] == '\n' || s[len - 1] == ' ' || s[len - 1] == '\t')
			&& len > start)
		len--;
	if (!(ret = ft_strsub(s, start, (len - start))))
		return (NULL);
	free(s);
	return (ret);
}
