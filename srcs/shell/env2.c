/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:41:47 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/09 00:01:32 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	add_set(char *var, char *value)
{
	if (ft_edit_env(g_set, var, value))
		return ;
	g_set = add_env(g_set, var, value);
}

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
