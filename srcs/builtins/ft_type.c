/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:54:53 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/15 17:30:10 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh.h"
#include "builtins.h"
#include "ft_printf.h"
#include "exec.h"

static int		type_search_folder(char *cmd)
{
	struct stat		tmp;

	if (access(cmd, F_OK) == 0)
	{
		stat(cmd, &tmp);
		if (S_ISDIR(tmp.st_mode))
			return (1);
		if (access(cmd, X_OK) == -1)
			return (1);
		return (0);
	}
	return (1);
}

static int		type_test_path(char *cmd)
{
	if (type_search_folder(cmd))
		return (1);
	return (0);
}

static char		*type_search_path(char *cmd, char **env)
{
	char			*fullpath;
	struct stat		tmp;
	char			**paths;
	int				i;

	(void)env;
	paths = get_env_path();
	i = -1;
	if (paths)
	{
		while (paths[++i])
		{
			fullpath = ft_vjoin(3, paths[i], "/", cmd);
			stat(fullpath, &tmp);
			if (access(fullpath, F_OK) == 0 && S_ISREG(tmp.st_mode))
			{
				free_tab(paths);
				return (fullpath);
			}
			fullpath = ft_free(fullpath);
		}
		free_tab(paths);
	}
	return (NULL);
}

static char		*type_test_env(char *cmd, char **env)
{
	char	*cmd_path;

	if ((cmd_path = type_search_path(cmd, env)))
	{
		
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
		{
			free(cmd_path);
			return (NULL);
		}
	}
	return (NULL);
}

int		ft_type(char **argv, char ***tenv)
{
	char	*full_path;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	if (count_arg(argv) < 1)
		return (0);
	while (argv[i])
	{
		if (lookforbuiltin(argv[i]))
			ft_printf("%s est un builtin de %s\n", argv[i], SHELL_NAME);
		else if (is_path(argv[i]))
		{
			if (type_test_path(argv[i]) == 0)
				ft_printf("%s est %s\n", argv[i], argv[i]);
			else
			{
				ret = 1;
				ft_dprintf(2, "%s: type: %s : non trouvé\n", SHELL_NAME, argv[i]);
			}
		}
		else
		{
			if ((full_path = type_test_env(argv[i], *tenv)))
				ft_printf("%s est %s\n", argv[i], full_path);
			else
			{
				ret = 1;
				ft_dprintf(2, "%s: type: %s : non trouvé\n", SHELL_NAME, argv[i]);
			}
			free(full_path);
		}
		++i;
	}
	return (ret);
}
