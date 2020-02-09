/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:57:57 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/09 17:27:16 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"

int		ft_exit(char **argv, char ***tenv)
{
	(void)tenv;
	g_exit = 0;
	if (argv[1])
		g_exit = ft_atoi(argv[1]);
	return (0);
}
