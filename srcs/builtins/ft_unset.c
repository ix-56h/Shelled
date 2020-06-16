/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:43:21 by ezonda            #+#    #+#             */
/*   Updated: 2020/06/08 12:20:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "sh.h"

int		ft_unset(char **argv, char ***set)
{
	int i;

	i = 0;
	(void)set;
	if (!argv[1])
	{
		ft_putendl_fd("42sh: unset: not enough arguments", 2);
		return (1);
	}
	else
	{
		while (g_set && argv[++i])
			g_set = del_var(g_set, argv[i]);
		i = 0;
		while (g_env && argv[++i])
			g_env = del_var(g_env, argv[i]);
	}
	return (0);
}
