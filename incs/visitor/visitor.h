/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:46:14 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/26 19:31:36 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_H
# define FT_VISITOR_H
# define WRITE_END 1
# define READ_END 0
# include "ast.h"
# include "tokenizer.h"
# include "double_linked_list.h"

typedef struct			s_pipe_list
{
	struct s_pipe_list	*next;
	struct s_pipe_list	*prev;
	int					fd[2];
	int					used;
}						t_pipe_list;
typedef struct			s_redir_list
{
	struct s_redir_list	*next;
	struct s_redir_list	*prev;
	int					in;
	int					out;
}						t_redir_list;
typedef struct			s_io_lists
{
	t_redir_list		*redir;
	t_pipe_list			*piped;
}						t_io_lists;
typedef					t_dl_node t_job;
typedef	struct			s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	pid_t				pid;
	char				is_finish;
	int					ret;
}						t_process;

t_job					*g_job_head;
int						(*g_visit_rules[TOK_POSIX_MAX])(t_node *node,
							t_io_lists io, t_job **job);
int						visit_cmd(t_node *node, t_io_lists io, t_job **job);
int						visit_or_if(t_node *node, t_io_lists io, t_job **job);
int						visit_and_if(t_node *node, t_io_lists io, t_job **job);
int						visit_pipe(t_node *node, t_io_lists io, t_job **job);
int						visit_dless(t_node *node, t_io_lists io, t_job **job);
int						visit_dgreat(t_node *node, t_io_lists io, t_job **job);
int						visit_lessand(t_node *node, t_io_lists io, t_job **job);
int						visit_greatand(t_node *node, t_io_lists io, t_job **job);
int						visit_lessgreat(t_node *node, t_io_lists io,
							t_job **job);
int						visit_left_redi(t_node *node, t_io_lists io,
							t_job **job);
int						visit_right_redi(t_node *node, t_io_lists io,
							t_job **job);
int						visit_semi(t_node *node, t_io_lists io, t_job **job);
int						visit(t_node *root, t_job **job);


t_process	*create_process(pid_t pid);
t_process	*find_process_by_pid(t_process *process, pid_t pid);
int			job_is_finish(t_job *job);
void		clean_job(void);

int	exec_great_and(t_node *node, t_io_lists *io, t_job **job);
int	exec_less_and(t_node *node, t_io_lists *io, t_job **job);
int	exec_right_redi(t_node *node, t_io_lists *io, t_job **job);
int	exec_left_redi(t_node *node, t_io_lists *io, t_job **job);
int	exec_dgreat(t_node *node, t_io_lists *io, t_job **job);
int	exec_dless(t_node *node, t_io_lists *io, t_job **job);
int	exec_pipe(t_node *node, t_io_lists *io, t_job **job, int *pipefd);
int	exec_command(t_node *node, t_io_lists *io, t_job **job);
#endif
