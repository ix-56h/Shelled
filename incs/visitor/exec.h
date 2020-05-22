/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:38:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/10 22:17:10 by akeiflin         ###   ########.fr       */
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
int		save_and_restore_fd(int action);

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
#endif
