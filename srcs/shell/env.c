/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:28:07 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/08 12:34:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <unistd.h>
#include "libft.h"
#include "hash.h"

char	**init_env(char **env)
{
	struct passwd	*pw;
	char			*tmp;
	char			cwd[FT_PATH_MAX];

	pw = getpwuid(getuid());
	if ((tmp = pw->pw_dir) && !(*getcwd(cwd, sizeof(cwd))))
		exit(EXIT_FAILURE);
	if (!(env = malloc(sizeof(char *) * 5)))
		exit(EXIT_FAILURE);
	if (!(env[0] = ft_strdup("SHLVL=0")))
		exit(EXIT_FAILURE);
	if (!(env[1] = ft_strdup("_=/usr/bin/env")))
		exit(EXIT_FAILURE);
	if (!(env[2] = ft_strdup("PWD=")))
		exit(EXIT_FAILURE);
	if (!(env[2] = ft_strjoinf(env[2], cwd, 1)))
		exit(EXIT_FAILURE);
	if (!(env[3] = ft_strdup("HOME=")))
		exit(EXIT_FAILURE);
	if (!(env[3] = ft_strjoinf(env[3], tmp, 1)))
		exit(EXIT_FAILURE);
	env[4] = 0;
	return (env);
}

/*
**	Copy and realloc all the `env'
**	Entry filled with "\0" whill be skipped
*/

char	**cpy_env(char **env)
{
	int		len;
	int		i;
	char	**head;
	char	**c_env;

	i = -1;
	len = 0;
	while (env[++i])
		if (ft_strcmp(env[i], "") != 0)
			++len;
	head = ft_calloc(sizeof(char *) * (len + 1));
	c_env = head;
	while (*env)
	{
		if (ft_strcmp(*env, "") != 0)
		{
			*c_env = ft_strdup(*env);
			++c_env;
			++env;
		}
		else
			++env;
	}
	return (head);
}

/*
**	Edit an entry in env
**	Return 1 or 0 if the value exist or not
*/

int		ft_edit_env(char **env, char *looking, char *value)
{
	char	*new_env;

	if (ft_strcmp(looking, "PATH") == 0)
		empty_table();
	while (env && *env)
	{
		if (ft_strcmp(*env, looking) == '=')
		{
			new_env = ft_vjoin(3, looking, "=", value);
			*env = ft_free(*env);
			*env = new_env;
			return (1);
		}
		++env;
	}
	return (0);
}

/*
**	Add a new entry in the env
**	Return new env (The list a a new malloc and the previous one is
**	already freed)
*/

char	**add_env(char **env, char *var, char *value)
{
	size_t		i;
	size_t		j;
	char		**new_env;
	char		*new_var;

	j = 0;
	i = 0;
	if (ft_strcmp(var, "PATH") == 0)
		empty_table();
	while (env && env[i])
		++i;
	i += 2;
	new_env = ft_calloc(sizeof(char *) * i);
	while (j < i - 2)
	{
		new_env[j] = env[j];
		j++;
	}
	env = ft_free(env);
	new_var = ft_vjoin(3, var, "=", value);
	new_env[j] = new_var;
	return (new_env);
}

/*
**	Remove the value, clone and free the old env
**	Return a new env
*/

char	**del_var(char **env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	if (ft_strcmp(var, "PATH") == 0)
		empty_table();
	while (env[i])
	{
		if (ft_strcmp(env[i], var) == '=')
		{
			env[i] = ft_free(env[i]);
			env[i] = ft_strdup("");
			new_env = cpy_env(env);
			free_env(env);
			return (new_env);
		}
		++i;
	}
	return (env);
}
