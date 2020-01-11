/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 00:40:27 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "visitor.h"
#include "sh.h"
#include "ast.h"

#define ERR_IS_FOLDER       1           //lel les defines ici
#define ERR_PATH_ACCES      2
#define ERR_NO_FILE         3
#define ERR_CMD_NOT_FOUND   4

void		free_tab(char **tab)
{
    char **head;

    head = tab;
	if (tab && *tab)
	{
		while (*tab)
        {
            free(*tab);
            ++tab;
        }
		free(head);
	}
}

int             err_exec(char *buff, int err)
{
    if (buff)
    {
        if (err == ERR_IS_FOLDER)
            ft_vprintfd(STDERR_FILENO, 3, SHELL_NAME": is a directory: ", buff, "\n");
        else if (err == ERR_PATH_ACCES)
            ft_vprintfd(STDERR_FILENO, 3, SHELL_NAME": permission denied: ", buff, "\n");
        else if (err == ERR_NO_FILE)
            ft_vprint(STDERR_FILENO, 3, SHELL_NAME": no such file or directory: ", buff, "\n");
        else if (err == ERR_CMD_NOT_FOUND)
            ft_vprint(STDERR_FILENO, 3, SHELL_NAME": command not found: ", buff, "\n");
    }
    return (err);
}


char	**get_env_path(void)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");   //gentenv a revoir si ca marche
	if (path)
	{
		paths = ft_strsplit(path, ':');
		return (paths);
	}
	else
		return (NULL);
}

/*
**	check if there is an error on the file
*/

static int		search_folder(t_node *cmd)
{
	struct stat		tmp;

	if (access(cmd->data, F_OK) == 0)
	{
		lstat(cmd->data, &tmp);
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

static char		*search_path(t_node *cmd, char **env)
{
	char			*fullpath;
	struct stat		tmp;
	char			**paths;
	int				i;

	paths = get_env_path();
    i = -1;
	if (paths)
	{
		while (paths[++i])
		{
			fullpath = ft_vjoin(3, paths[i], "/", cmd->data);
			lstat(fullpath, &tmp);
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

int				test_path(t_node *cmd)
{
	int		ft_err;

	ft_err = search_folder(cmd);
	return (err_exec(cmd->data, ft_err));
}

/*
**	check if there is an error on the file
*/

int				test_env(t_node *cmd, char **env, char **cmd_path)
{
	if ((*cmd_path = search_path(cmd, env)))
	{
		if (access(*cmd_path, X_OK) == 0)
			return (0);
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

static int		is_path(char *buff)
{
	if (ft_strchr(buff, '/') != NULL)
		return (1);
	return (0);
}

int				exec_cmd(t_node *cmd, char ***env)
{
	//t_builtin	func;
	int			err;
    char        *cmd_path;

    cmd_path = NULL;
	err = 0;
	/*if (!altenv && (func = get_builtin_func(cmd->cmd)))
		return (func(cmd->args, env));*/
    //if (ft_strcmp(cmd->data, "setenv"))
	if (is_path(cmd->data))
	{
		if ((err = test_path(cmd)) == 0)
            execve(cmd->data, cmd->args, ((env) ? *env : g_env));
	}
	else
	{
		if ((err = test_env(cmd, *env, &cmd_path)) == 0)
			execve(cmd_path, cmd->args, ((env) ? *env : g_env));
	}
	return (err);
}
