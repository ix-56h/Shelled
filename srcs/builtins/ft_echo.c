/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:54:14 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/09 00:00:21 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"

char	**echo_arg(char **argv, int *arg_n)
{
	char	*arg;

	while (*(++argv))
	{
		arg = *argv;
		if (!(*arg))
			continue ;
		if (*arg && *arg != '-')
			break ;
		while (*(++arg))
			if (*arg != 'n')
				break ;
		if (*(arg))
			break ;
		else
			*arg_n = 1;
	}
	return (argv);
}

int		ft_echo(char **argv, char ***tenv)
{
	int		arg_n;

	(void)tenv;
	arg_n = 0;
	argv = echo_arg(argv, &arg_n);
	while (*argv)
	{
		ft_putstr(*argv);
		if (*(++argv))
			ft_putchar(' ');
	}
	if (!arg_n)
		ft_putchar('\n');
	return (0);
}
