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

#include <stdio.h>

void	test_hash(char *param)
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

void	get_split_args(char **av)
{
	int		i;
	int		j;
	char	**split;
	char	*param;

	i = 1;
	j = 0;
	param = ft_strdup("( A B C D E F G H I J )");
	add_set("@", param);
	test_hash(param);
/*	while (av[i])
	{
		split = ft_strsplit(av[i], ' ');
		printf("\nHERE split 0 : |%s|\n", split[0]);
	//	param[j] = split[0][0];
		param = ft_strjoinf(param, split[0], 1);
	printf("\nparam : |%s|\n", param);
		printf("\nHERE2\n");
		param[j++] = ' ';
		printf("\nHERE3\n");
		ft_free(split);
		printf("\nHERE4\n");
		i++;
		printf("\nHERE5\n");
		j++;
		printf("\nHERE6\n");
	}
	printf("\nparam : |%s|\n", param);*/
//	j = 0;
//	while (param[j])
//		printf("\nparam : |%s|\n", param[j++]);
	
}

int		ft_set(char **argv, char ***set)
{
	int i;

	i = 0;
	(void)set;
	if (!argv[1])
		while (g_set[i])
			ft_putendl_fd(g_set[i++], 1);
	else
		get_split_args(argv);
//		printf("\nargs\n");
	return (0);
}
