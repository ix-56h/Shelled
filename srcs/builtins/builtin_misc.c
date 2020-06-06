/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:40:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/06 20:11:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtins_jump.h"
#include "sh.h"

int			count_arg(char **argv)
{
	int	i;

	i = -1;
	while (*argv)
	{
		++i;
		++argv;
	}
	return (i);
}

t_builtin	lookforbuiltin(char *data)
{
	int cpt;

	cpt = 0;
	if (ft_strcmp(data, "exit") != 0)
		g_ready_exit = 0;
	while (g_builtins[cpt].command)
	{
		if (!ft_strcmp(g_builtins[cpt].command, data))
			return (g_builtins[cpt].builtin);
		cpt++;
	}
	return (NULL);
}
