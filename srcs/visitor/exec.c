/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 23:19:16 by akeiflin         ###   ########.fr       */
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
#include "builtins.h"
#include "builtin_rules.h"

typedef int	(*t_builtin)(char **, char ***); //lel a enlever d'ici

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
            ft_vprintfd(STDERR_FILENO, 3, SHELL_NAME": no such file or directory: ", buff, "\n");
        else if (err == ERR_CMD_NOT_FOUND)
            ft_vprintfd(STDERR_FILENO, 3, SHELL_NAME": command not found: ", buff, "\n");
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



int				exec_with_fork(t_node *cmd, char **env, t_io_lists io, char *cmd_path)
{
	char	*program;
	int		pid;
	
	program = (cmd_path) ? cmd_path : cmd->data;
	if ((pid = fork()) == -1)
		return (0);
	else if (pid == 0) //FILS
	{
		set_pipe_fd(io.piped);
		set_redir_fd(io.redir);
		execve(program, cmd->args, ((env) ? env : g_env));
		exit(1);
	}
	else //PARENT
	{
		close_used_pipe_fd(io.piped);
		set_used_fd(io.piped);
		return (1);
	}
}

int     save_and_restore_fd(int action)
{
    static int  fds[3] = {-1};

    if (action == 0)                                //Save stdin/out/err
    {
        fds[STDIN_FILENO] = dup(STDIN_FILENO);
        fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
        fds[STDERR_FILENO] = dup(STDERR_FILENO);
    }
    else if (action == 1)                           //Restore stdin/out/err
    {
        dup2(fds[STDIN_FILENO], STDIN_FILENO);
        close(fds[STDIN_FILENO]);
        dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
        close(fds[STDOUT_FILENO]);
        dup2(fds[STDERR_FILENO], STDERR_FILENO);
        close(fds[STDERR_FILENO]);
    }
    return (1);
}

t_builtin lookforbuiltin(char *data)
{
	if (ft_strcmp(data, "addpath") == 0)
		return (ft_addpath);
	if (ft_strcmp(data, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(data, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(data, "setenv") == 0)
		return (ft_setenv);
	if (ft_strcmp(data, "take") == 0)
		return (ft_take);
	if (ft_strcmp(data, "unsetenv") == 0)
		return (ft_unsetenv);
	return (NULL);
}

int				exec_without_fork(t_node *cmd, char **env, t_io_lists io)
{
		t_builtin exec_builtin;
		save_and_restore_fd(0);
		set_pipe_fd(io.piped);
		set_redir_fd(io.redir);
		exec_builtin = lookforbuiltin(cmd->data);
		exec_builtin(cmd->args, ((env) ? &env : &g_env));
		close_used_pipe_fd(io.piped);
		save_and_restore_fd(1);
		set_used_fd(io.piped);
		return (1);
}

int				exec_cmd(t_node *cmd, char **env, t_io_lists io)
{
	//t_builtin	func;
	int			err;
    char        *cmd_path;

    cmd_path = NULL;
	err = 0;
	/*if (!altenv && (func = get_builtin_func(cmd->cmd)))
		return (func(cmd->args, env));*/
    if (lookforbuiltin(cmd->data))
		exec_without_fork(cmd, env, io); //exec witout fork
	else if (is_path(cmd->data))
	{
		if ((err = test_path(cmd)) == 0)
            exec_with_fork(cmd, env, io, NULL);
	}
	else
	{
		if ((err = test_env(cmd, env, &cmd_path)) == 0)
		{
			exec_with_fork(cmd, env, io, cmd_path);
			ft_free(cmd_path);
		}
	}
	return (err);
}
