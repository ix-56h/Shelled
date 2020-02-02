/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:46:14 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 00:32:31 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_H
# define FT_VISITOR_H
# define WRITE_END 1
# define READ_END 0
# include "ast.h"
# include "tokenizer.h"

typedef struct s_pipe_list
{
    struct s_pipe_list  *next;
    struct s_pipe_list  *prev;
    int     fd[2];
    int     used;
}               t_pipe_list;
typedef struct s_redir_list
{
    struct s_redir_list  *next;
    struct s_redir_list  *prev;
    int                 in;
    int                 out;
}               t_redir_list;
typedef struct  s_io_lists
{
    t_redir_list    *redir;
    t_pipe_list     *piped;
}               t_io_lists;
int	(*G_VISIT_RULES[TOK_POSIX_MAX]) (t_node *node, t_io_lists io, int *rets);
int	visit_cmd(t_node *node, t_io_lists io, int *rets);
int	visit_or_if(t_node *node, t_io_lists io, int *rets);
int	visit_and_if(t_node *node, t_io_lists io, int *rets);
int	visit_pipe(t_node *node, t_io_lists io, int *rets);
int	visit_dless(t_node *node, t_io_lists io, int *rets);
int	visit_dgreat(t_node *node, t_io_lists io, int *rets);
int	visit_lessand(t_node *node, t_io_lists io, int *rets);
int	visit_greatand(t_node *node, t_io_lists io, int *rets);
int	visit_lessgreat(t_node *node, t_io_lists io, int *rets);
int	visit_left_redi(t_node *node, t_io_lists io, int *rets);
int	visit_right_redi(t_node *node, t_io_lists io, int *rets);
int	visit_semi(t_node *node, t_io_lists io, int *rets);
int	visit(t_node *root);
#endif
