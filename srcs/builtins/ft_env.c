/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:47:22 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/01 04:57:34 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"
#include "ast.h"
#include "visitor.h"

static void	printenv(char **env)
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

static char	*ft_strschr(const char *s, int c)
{
	if (s && *s)
	{
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}

static void	ft_env_sub(char ***tenv, char ***env, char **argv)
{
	t_node		node;
	t_io_lists	io;

	(void)tenv;
	io = (t_io_lists) {NULL, NULL};
	if ((node.data = *argv))
	{
		node.args = argv;
		exec_cmd(&node, *env, io);
	}
	else
		printenv(*env);
	free_env(*env);
}

int			ft_env(char **argv, char ***tenv)
{
	char	**env;
	char	*value;

	if (*(++argv) && ft_strcmp(*argv, "-i") == 0)
		env = NULL;
	else
	{
		env = cpy_env(*tenv);
		--argv;
	}
	while (++argv)
	{
		if (*argv && **argv != '=' && (value = ft_strschr(*argv, '=')))
		{
			*value = 0;
			++value;
			if (!ft_edit_env(env, *argv, value))
				env = add_env(env, *argv, value);
		}
		else
			break ;
	}
	ft_env_sub(tenv, &env, argv);
	return (0);
}
