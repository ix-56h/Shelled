/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:47:22 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/09 21:42:10 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "builtins.h"

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

/*static void	ft_env_sub(t_cmd *cmd, char ***tenv, char ***env, char **argv)
{
	if ((cmd->cmd = *argv))
	{
		cmd->args = argv;
		//exec_cmd(cmd, tenv, env); lel
		ft_free(cmd->fullpath);
	}
	else
		printenv(*env);
	free_env(*env);
}

int			ft_env(char **argv, char ***tenv)
{
	char	**env;
	char	*value;
	t_cmd	cmd;

	if (*(++argv) && ft_strcmp(*argv, "-i") == 0)
		env = NULL;
	else
	{
		env = clone_env(*tenv);
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
	ft_env_sub(&cmd, tenv, &env, argv);
	return (0);
}
*/