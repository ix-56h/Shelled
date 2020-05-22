/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:37:55 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/23 14:16:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *mem;

	if (!(mem = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(mem, size);
	mem[size] = '\0';
	return (mem);
}
