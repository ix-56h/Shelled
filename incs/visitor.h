/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:46:14 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/01 20:19:39 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_H
# define FT_VISITOR_H
# define WRITE_END 0
# define READ_END 1

typedef  struct s_pipe_list
{
    struct s_pipe_list  *next;
    struct s_pipe_list  *prev;
    int     fd[2];
    int     used;
}               t_pipe_list;

int	visit_cmd(t_node *node, t_pipe_list *piped);
int	visit_or_if(t_node *node, t_pipe_list *piped);
int	visit_and_if(t_node *node, t_pipe_list *piped);
int	visit_pipe(t_node *node, t_pipe_list *piped);
int	visit_dless(t_node *node, t_pipe_list *piped);
int	visit_dgreat(t_node *node, t_pipe_list *piped);
int	visit_lessand(t_node *node, t_pipe_list *piped);
int	visit_greatand(t_node *node, t_pipe_list *piped);
int	visit_lessgreat(t_node *node, t_pipe_list *piped);
int	visit_left_redi(t_node *node, t_pipe_list *piped);
int	visit_right_redi(t_node *node, t_pipe_list *piped);
int	visit_semi(t_node *node, t_pipe_list *piped);
int	visit(t_node *root);

#endif
