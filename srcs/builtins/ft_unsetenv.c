/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:11:17 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 22:06:31 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"

int		ft_unsetenv(char **argv, char ***env)
{
	int		i;

	i = count_arg(argv);
	if (i == 0)
		ft_putendl("unsetenv: Too few arguments.");
	else if (i >= 1)
		*env = del_var(*env, argv[1]);
	return (1);
}
