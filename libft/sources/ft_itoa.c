/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:16:29 by niguinti          #+#    #+#             */
/*   Updated: 2019/06/20 20:28:43 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_itoa(long long int n)
{
	long long int	nbr;
	int				sign;
	int				len;
	char			*alpha;

	sign = (n < 0 ? 1 : 0);
	alpha = NULL;
	len = ft_size_digit(n);
	nbr = (n < 0 ? -n : n);
	if (!(alpha = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	alpha[len--] = '\0';
	while (len >= 0)
	{
		alpha[len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	if (sign == 1)
		alpha[0] = '-';
	return (alpha);
}
