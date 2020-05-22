/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:24:20 by niguinti          #+#    #+#             */
/*   Updated: 2019/07/30 20:33:08 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinf(char *s1, char *s2, short type)
{
	char	*str;

	if (!(str = ft_strjoin(s1, s2)))
		return (NULL);
	if (type == 1 || type == 3)
	{
		if (s1)
			free(s1);
	}
	if (type == 2 || type == 3)
	{
		if (s2)
			free(s2);
	}
	return (str);
}
