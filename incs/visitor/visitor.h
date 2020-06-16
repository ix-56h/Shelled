/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:46:14 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/15 20:48:21 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_H
# define FT_VISITOR_H
# include "ast.h"
# include "visitor_misc.h"
# include "job.h"

int			visit_assign_word(t_node *node, t_io_lists io, t_job **job);
int			visit_cmd(t_node *node, t_io_lists io, t_job **job);
int			visit_or_if(t_node *node, t_io_lists io, t_job **job);
int			visit_and_if(t_node *node, t_io_lists io, t_job **job);
int			visit_pipe(t_node *node, t_io_lists io, t_job **job);
int			visit_dless(t_node *node, t_io_lists io, t_job **job);
int			visit_dgreat(t_node *node, t_io_lists io, t_job **job);
int			visit_lessand(t_node *node, t_io_lists io, t_job **job);
int			visit_greatand(t_node *node, t_io_lists io, t_job **job);
int			visit_left_redi(t_node *node, t_io_lists io, t_job **job);
int			visit_right_redi(t_node *node, t_io_lists io, t_job **job);
int			visit_semi(t_node *node, t_io_lists io, t_job **job);
int			visit(t_node *root, char *cmd, t_dl_node *redir);
int			visit_background(t_node *node, t_io_lists io, t_job **job);

char		*substitution_wrapper(char *tmp);

int			exec_great_and(t_node *node, t_io_lists *io, t_job **job);
int			exec_less_and(t_node *node, t_io_lists *io, t_job **job);
int			exec_right_redi(t_node *node, t_io_lists *io, t_job **job);
int			exec_left_redi(t_node *node, t_io_lists *io, t_job **job);
int			exec_dgreat(t_node *node, t_io_lists *io, t_job **job);
int			exec_dless(t_node *node, t_io_lists *io, t_job **job);
int			exec_pipe(t_node *node, t_io_lists *io, t_job **job, int *pipefd);
int			exec_command(t_node *node, t_io_lists *io, t_job **job);

int			is_only_assign(t_node *node);
void		restore_env_back(t_node *node);
void		restore_env(char *data, char *old_value);
void		assign_var(char *data, char *value, int mod);

int			visit_assign_redir(t_node *node, t_io_lists *io, t_job **job);
void		visit_assign_pipe(t_node *node, t_io_lists *io, t_job **job,
			int *pipe);

size_t		get_end_grouped_cmd(char *cmd, size_t i);
size_t		get_end_subshell(char *cmd, size_t i);
size_t		get_next_double_cote(char *cmd, size_t i);
size_t		get_next_cote(char *cmd, size_t i);
size_t		get_next_semi_col(char *cmd);
size_t		get_next_and(char *cmd);

#endif
