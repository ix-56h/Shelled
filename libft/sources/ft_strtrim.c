/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:06:04 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 16:54:08 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	size_t			len;
	unsigned int	start;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == '\n' || s[start] == ' ' || s[start] == '\t')
		start++;
	len = ft_strlen(s);
	while ((s[len - 1] == '\n' || s[len - 1] == ' ' || s[len - 1] == '\t')
			&& len > start)
		len--;
	return (ft_strsub(s, start, (len - start)));
}
