/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_and_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:37:06 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/07 21:42:48 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "builtins.h"
#include "exec.h"
#include "hash.h"

/*
**	check if there is an error on the file
*/

int		search_folder(t_node *cmd)
{
	struct stat		tmp;

	if (access(cmd->data, F_OK) == 0)
	{
		stat(cmd->data, &tmp);
		if (S_ISDIR(tmp.st_mode))
			return (ERR_IS_FOLDER);
		if (access(cmd->data, X_OK) == -1)
			return (ERR_PATH_ACCES);
		return (0);
	}
	return (ERR_NO_FILE);
}

/*
**	check if there is an error on the file
*/

char	*search_path(t_node *cmd, char **env)
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
			fullpath = ft_vjoin(3, paths[i], "/", cmd->data);
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

int		test_path(t_node *cmd)
{
	int		ft_err;

	ft_err = search_folder(cmd);
	return (err_exec(cmd->data, ft_err));
}

/*
**	check if there is an error on the file
*/

int		test_env(t_node *cmd, char **env)
{
	char	*cmd_path;

	if ((cmd_path = search_table(cmd->data))
		|| (cmd_path = search_path(cmd, env)))
	{
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd->data);
			cmd->data = cmd_path;
			return (0);
		}
		else
			return (err_exec(cmd->data, ERR_PATH_ACCES));
	}
	else
		return (err_exec(cmd->data, ERR_CMD_NOT_FOUND));
}

/*
**	choise if my cmd is a builtin, executable or a command system
**	return the cmd return value after execution
*/

int		is_path(char *buff)
{
	if (ft_strchr(buff, '/') != NULL)
		return (1);
	return (0);
}
