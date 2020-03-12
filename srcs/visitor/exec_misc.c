/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:49:31 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/12 04:14:02 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "builtins.h"

void	free_tab(char **tab)
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

int		err_exec(char *buff, int err)
{
	if (buff)
	{
		if (err == ERR_IS_FOLDER)
			ft_vprintfd(STDERR_FILENO, 3\
					, SHELL_NAME": is a directory: ", buff, "\n");
		else if (err == ERR_PATH_ACCES)
			ft_vprintfd(STDERR_FILENO, 3\
					, SHELL_NAME": permission denied: ", buff, "\n");
		else if (err == ERR_NO_FILE)
			ft_vprintfd(STDERR_FILENO, 3\
					, SHELL_NAME": no such file or directory: ", buff, "\n");
		else if (err == ERR_CMD_NOT_FOUND)
			ft_vprintfd(STDERR_FILENO, 3\
					, SHELL_NAME": command not found: ", buff, "\n");
		else if (err == ERR_REDIR)
			ft_vprintfd(STDERR_FILENO, 3\
					, SHELL_NAME": redirection error: ", buff, "\n");
	}
	return (err);
}

char	**get_env_path(void)
{
	char	*path;
	char	**paths;

	path = get_env(g_env, "PATH");
	if (path)
	{
		paths = ft_strsplit(path, ':');
		return (paths);
	}
	else
		return (NULL);
}

char	*cut_command(char *cmd, char act)
{
	int		i = 0;
	char	*res;
	int		len;

	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'')
		{
			while (cmd[i] && cmd[i] != '\'')
				++i;
			++i;
		}
		else if (cmd[i] == '"')
		{
			while (cmd[i] && cmd[i] != '"')
			{
				if (cmd[i] == '\\')
					i += 2;
				else
					++i;
			}
			++i;
		}
		else if (cmd[i] == ';')
			break;
		else
			++i;
	}
	cmd[i] = '\0';
	res = ft_strdup(cmd);
	cmd[i] = ';';
	if (act == 1)
	{
		len = ft_strlen(&(cmd[i + 1]));
		ft_memcpy(cmd, &(cmd[i + 1]), len);
		cmd[len] = '\0';
	}
	return (res);
}