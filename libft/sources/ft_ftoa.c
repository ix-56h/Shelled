/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:26:51 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/18 03:30:47 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_process(long double f, short prec)
{
	char	*str;
	short	i;

	i = 0;
	if (!(str = malloc(sizeof(char) * prec + 1)))
		return (NULL);
	str[prec] = 0;
	while (prec-- != 0)
	{
		f *= 10;
		str[i++] = (char)(f + '0');
		f -= (long long int)f;
	}
	return (str);
}

char	*ft_ftoa(long double f, short prec)
{
	char			*str;

	if (!(str = ft_itoa(f)))
		return (NULL);
	if (!prec)
		return (str);
	if (!(str = ft_strjoinf(str, ".", 1)))
		return (NULL);
	f = (f - (long long int)f) * (f < 0 ? -1 : 1);
	if (!(str = ft_strjoinf(str, ft_process(f, prec), 3)))
		return (NULL);
	return (str);
}
