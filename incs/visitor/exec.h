/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:38:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 01:40:20 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ast.h"
# include "visitor_misc.h"

int		set_pipe_fd(t_pipe_list *piped);
int		close_used_pipe_fd(t_pipe_list *piped);
void	close_all_pipe(t_io_lists io);
int		set_used_fd(t_pipe_list *piped);
int		set_redir_fd(t_redir_list *redir);
int		apply_fd(t_io_lists io);

int		exec_cmd(t_node *cmd, char **env, t_io_lists io, t_job *job);
int		exec_heredoc(t_fifo *stack);

int		search_folder(t_node *cmd);
char	*search_path(t_node *cmd, char **env);
int		test_path(t_node *cmd);
int		test_env(t_node *cmd, char **env);
int		is_path(char *buff);

void	free_tab(char **tab);
int		err_exec(char *buff, int err);
char	**get_env_path(void);
int		need_background(t_io_lists *io);

int		exec_builtin_no_fork(t_node *cmd, char **env, t_job *job);
void	child_exec_forked(t_io_lists io, char **env, t_job *job, t_node *cmd);
void	after_fork_routine(pid_t pid, t_io_lists io, t_job *job);
int		exec_subshell(t_node *node, t_io_lists *io, t_job **job);
int		subshell_wrapper(t_node *node, t_io_lists *io, t_job **job);
void	grp_cmd_wrapper(t_io_lists *io);

#endif
