/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:06:58 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/09 21:58:28 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "sh.h"
#include "builtins.h"

/*
**	builtin take:
**	create and cd in a folder
*/

static int	ft_take_err(char *str, int error)
{
	ft_vprint(3, "minishell: command not found: ", str, "\n");
	return (error);
}

int			ft_take(char **argv, char ***env)
{
	int		argc;

	argc = count_arg(argv);
	if (argc == 1)
	{
		if (access(argv[1], F_OK) != 0)
		{
			if (mkdir(argv[1], 0755) == -1)
				return (ft_take_err(argv[1], 0));
		}
		ft_cd(argv, env);
	}
	else
		ft_putendl("usage: take <filename>");
	return (0);
}
