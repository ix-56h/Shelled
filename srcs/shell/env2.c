/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:41:47 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 05:42:24 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		++i;
	}
	if (env && env[i])
		free(env[i]);
	free(env);
}

char	*get_env(char **env, char *looking)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (env && *env)
	{
		if (ft_strcmp(*env, looking) == '=')
			break ;
		env++;
	}
	if (env && *env)
		return ((*env) + ft_strlen(looking) + 1);
	return (NULL);
}
