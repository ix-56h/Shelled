/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:43:21 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 13:08:21 by ezonda           ###   ########.fr       */
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
		ft_putendl_fd("unset: Too few arguments.", 2);
	else
		while (g_set && argv[++i])
			g_set = del_var(g_set, argv[i]);
	i = 0;
	while (g_env && argv[++i])
		ft_unsetenv(argv, &g_env);
	return (0);
}
