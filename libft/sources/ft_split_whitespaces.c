/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:52:19 by niguinti          #+#    #+#             */
/*   Updated: 2019/06/05 02:17:22 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_cntwords(char *str)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i])
		words = 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r')
		{
			while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
					|| str[i] == '\r')
				i++;
			if (str[i])
				words++;
		}
		i++;
	}
	return (words);
}

int		is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

char	**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		words;
	int		i;
	int		x;

	words = ft_cntwords(str);
	x = -1;
	if (!(tab = (char **)malloc(sizeof(char*) * (words + 1))))
		return (0);
	while (++x < words)
	{
		while (is_blank(*str) == 1)
			str++;
		i = 0;
		while (is_blank(str[i]) == 0)
			i++;
		if (!(tab[x] = (char *)malloc(sizeof(char) * (i + 1))))
			return (0);
		ft_bzero(tab[x], i + 1);
		ft_strncpy(tab[x], str, i);
		str += i;
	}
	tab[x] = 0;
	return (tab);
}
