/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:45:39 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 14:25:44 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	int		i;
	char	*str;

	if (s == NULL || !(*f) || !(str = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(str[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
