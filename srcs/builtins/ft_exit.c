/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:57:57 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 07:09:00 by niguinti         ###   ########.fr       */
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
	return (1);
}
