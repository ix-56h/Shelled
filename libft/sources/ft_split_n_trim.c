/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_n_trim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:20:01 by niguinti          #+#    #+#             */
/*   Updated: 2019/08/10 13:24:53 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_n_trim(char *s, char c)
{
	char	**ret;
	size_t	i;

	i = 0;
	if (!(ret = ft_strsplit(s, c)))
		return (NULL);
	while (ret[i])
	{
		ret[i] = ft_strtrimf(ret[i]);
		i++;
	}
	return (ret);
}
