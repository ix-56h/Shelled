/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/11 20:53:54 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "visitor.h"

#define ERR_IS_FOLDER 1

/*ft_putstr_fd("", STDERR_FILENO);
int             err_exec(int err)
{
    if (err == ERR_IS_FOLDER)
        ft_putstr_fd("", STDERR_FILENO);
    return (err);
}*/

/*
**	check if there is an error on the file
*/

static int		search_folder(t_cmd *cmd)
{
	struct stat		tmp;

	if (access(cmd->cmd, F_OK) == 0)
	{
		cmd->fullpath = (ft_strdup(cmd->cmd));
		lstat(cmd->fullpath, &tmp);
		if (S_ISDIR(tmp.st_mode))
			return (ERR_IS_FOLDER);
		if (access(cmd->fullpath, X_OK) == -1)
			return (ERR_PATH_ACCES);
		return (0);
	}
	else
		return (ERR_NO_FILE);
}

/*
**	check if there is an error on the file
*/

static char		*search_path(t_cmd *cmd, char **env)
{
	char			*fullpath;
	struct stat		tmp;
	char			**paths;
	int				i;

	paths = get_env_path(env);
	if (paths && (i = -1) == -1)
	{
		while (paths[++i])
		{
			fullpath = ft_vjoin(3, paths[i], "/", cmd->cmd);
			lstat(fullpath, &tmp);
			if (access(fullpath, F_OK) == 0 && S_ISREG(tmp.st_mode))
			{
				free_tab(paths);
				return (fullpath);
			}
			fullpath = ft_free(fullpath);
		}
		free_tab(paths);
		return (NULL);
	}
	free_tab(paths);
	return (NULL);
}

int				exec_path(t_cmd *cmd)
{
	int		ft_err;

	ft_err = 0;
	ft_err = search_folder(cmd);
	if (ft_err < 0)
		err_minishell(cmd->cmd, ft_err);
	return (0);
}

/*
**	check if there is an error on the file
*/

int				exec_env(t_cmd *cmd, char ***env)
{
	if ((cmd->fullpath = search_path(cmd, *env)))
	{
		if (access(cmd->fullpath, X_OK) == 0)
			return (0);
		else
			return (err_minishell(cmd->cmd, ERR_PATH_ACCES));
	}
	else
		return (err_minishell(cmd->cmd, ERR_CMD_NOT_FOUND));
}

/*
**	choise if my cmd is a builtin, executable or a command system
**	return the cmd return value after execution
*/

int				exec_cmd(t_cmd *cmd, char ***env, char ***altenv)
{
	int			a_path;
	t_builtin	func;
	int			err;

	err = 0;
	a_path = is_path(cmd->cmd);
	if (!altenv && (func = get_builtin_func(cmd->cmd)))
		return (func(cmd->args, env));
	if (a_path)
	{
		if ((err = exec_path(cmd)) == 0)
			return (run_cmd(cmd, ((!altenv) ? *env : *altenv)));
	}
	else if (!a_path)
	{
		if ((err = exec_env(cmd, env)) == 0)
			return (run_cmd(cmd, ((!altenv) ? *env : *altenv)));
	}
	return (ERR_UNKNOW);
}
