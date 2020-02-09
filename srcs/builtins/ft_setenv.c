/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:38:03 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/09 02:29:17 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"

static void			printenv(char **env)
{
	if (env)
	{
		while (*env)
		{
			ft_putendl(*env);
			++env;
		}
	}
}

int					ft_setenv(char **argv, char ***env)
{
	int		i;

	i = count_arg(argv);
	if (i == 0)
	{
		printenv(*env);
		return (0);
	}
	else if (i == 1)
	{
		if (!ft_edit_env(*env, argv[1], NULL))
			*env = add_env(*env, argv[1], NULL);
	}
	else if (i == 2)
	{
		if (!ft_edit_env(*env, argv[1], argv[2]))
			*env = add_env(*env, argv[1], argv[2]);
	}
	else
	{
		ft_putendl("setenv: Too many arguments.");
		return (1);
	}
	return (0);
}
