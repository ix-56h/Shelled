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
#include "ft_printf.h"

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
		if (!ft_strcmp(arg, "-"))
			break ;
		while (*(arg++))
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
	if (fcntl(1, F_GETFD) != 0)
	{
		ft_putstr_fd("42sh: echo: write error: bad file descriptor\n", 2);
		return (1);
	}
	arg_n = 0;
	argv = echo_arg(argv, &arg_n);
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*(++argv))
			ft_putchar_fd(' ', 1);
	}
	if (!arg_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
