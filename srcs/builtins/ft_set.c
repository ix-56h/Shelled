/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:38:35 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 13:46:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "sh.h"

static void		add_param_count(char *param)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (param[i])
	{
		if (ft_isalnum(param[i]))
			count++;
		i++;
	}
	add_set("#", ft_itoa(count));
}

static char		*get_set_param(char **av)
{
	int		i;
	char	*str;

	i = 1;
	str = ft_strnew(2);
	str[0] = '(';
	str[1] = ' ';
	while (av[i])
	{
		str = ft_strjoinf(str, av[i], 1);
		if (av[i + 1])
			str = ft_strjoinf(str, " ", 1);
		i++;
	}
	str = ft_strjoinf(str, " )", 1);
	return (str);
}

static void		get_set_args(char **av)
{
	char	*param;

	param = get_set_param(av);
	add_set("@", param);
	add_param_count(param);
}

int				ft_set(char **argv, char ***set)
{
	int i;

	i = 0;
	(void)set;
	if (!argv[1])
		while (g_set[i])
			ft_putendl_fd(g_set[i++], 1);
	else
		get_set_args(argv);
	return (0);
}
