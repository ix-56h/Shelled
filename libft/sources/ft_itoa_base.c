/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 04:59:17 by niguinti          #+#    #+#             */
/*   Updated: 2019/03/07 15:23:40 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa_base(int value, int base, int caps)
{
	char	*s;
	long	n;
	int		sign;
	int		x[2];

	if (caps == 1)
		x[1] = 'A';
	else
		x[1] = 'a';
	n = (value < 0) ? -(long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	x[0] = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		x[0]++;
	if (!(s = (char*)malloc(sizeof(char) * (x[0] + 1))))
		return (NULL);
	s[x[0]] = '\0';
	n = (value < 0) ? -(long)value : value;
	while (x[0]-- + sign)
	{
		s[x[0]] = (n % base < 10) ? n % base + '0' : n % base + x[1] - 10;
		n /= base;
	}
	(x[0] == 0) ? s[x[0]] = '-' : 0;
	return (s);
}
