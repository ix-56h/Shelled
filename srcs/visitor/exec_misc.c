/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:49:31 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/20 18:31:06 by akeiflin         ###   ########.fr       */
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
		add_set("?", "1");
	}
	if (err == ERR_CMD_NOT_FOUND)
		add_set("?", "127");
	return (err);
}

char	**get_env_path(void)
{
	char	*path;
	char	**paths;

	path = get_env(g_set, "PATH");
	if (path)
	{
		paths = ft_strsplit(path, ':');
		return (paths);
	}
	else
		return (NULL);
}
