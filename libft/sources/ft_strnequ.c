/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:59:25 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/18 19:35:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (!(s1) || !(s2))
		return (0);
	if (!(*s1) && !(*s2))
		return (1);
	if (n == 0)
		return (1);
	if (*s1 == *s2)
		return (ft_strnequ(s1 + 1, s2 + 1, n - 1));
	return (0);
}
