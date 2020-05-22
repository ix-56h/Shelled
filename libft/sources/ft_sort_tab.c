/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 00:38:23 by niguinti          #+#    #+#             */
/*   Updated: 2019/05/17 00:40:36 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_tab(char **tab, int (*f)())
{
	int		i;
	int		j;
	char	*swp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (f(tab[i], tab[j]) > 0)
			{
				swp = tab[i];
				tab[i] = tab[j];
				tab[j] = swp;
			}
			j++;
		}
		i++;
	}
}
