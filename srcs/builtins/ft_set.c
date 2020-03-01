/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:38:35 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 13:46:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "sh.h"

int		ft_set(char **argv, char ***set)
{
	int i;

	i = 0;
	(void)set;
	if (!argv[1])
		while (g_set[i])
			ft_putendl_fd(g_set[i++], 1);
	return (0);
}
