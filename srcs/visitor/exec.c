/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/02 23:57:01 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "builtins.h"
#include "exec.h"

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
		close_unused_pipe_fd(io.piped);
		set_redir_fd(io.redir);
		execve(program, cmd->args, ((env) ? env : g_env));
		exit(1);
	}
	else //PARENT
	{
		close_used_pipe_fd(io.piped);
		return (1);
	}
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
