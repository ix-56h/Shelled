/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:43:40 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 21:08:40 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long		ft_abs(int c)
{
	long	nb;

	nb = (long)c;
	return ((nb < 0) ? nb * -1 : nb);
}

static int		ft_numlen(int nb)
{
	long	res;
	long	nbcp;

	nbcp = (long)nb;
	res = 0;
	if (nbcp == 0)
		return (1);
	nbcp = ft_abs(nb);
	while (nbcp >= 1)
	{
		res++;
		nbcp = nbcp / 10;
	}
	return (res);
}

char			*ft_itoa(long long n)
{
	long long		numlen;
	int				positive;
	char			*str;
	long long		num;

	numlen = ft_numlen(n);
	positive = ((n >= 0) ? 1 : 0);
	if (!positive)
		numlen++;
	if (!(str = ft_strnew(numlen)))
		return (NULL);
	if (!positive)
		str[0] = '-';
	num = ft_abs(n);
	while ((!positive) ? numlen - 1 : numlen)
	{
		str[--numlen] = '0' + num % 10;
		num /= 10;
	}
	return (str);
}
