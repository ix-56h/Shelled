/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:46:14 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/23 06:42:59 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_H
# define FT_VISITOR_H

int	visit_cmd(t_node *node);
int	visit_or_if(t_node *node);
int	visit_and_if(t_node *node);
int	visit_pipe(t_node *node);
int	visit_dless(t_node *node);
int	visit_dgreat(t_node *node);
int	visit_lessand(t_node *node);
int	visit_greatand(t_node *node);
int	visit_lessgreat(t_node *node);
int	visit_left_redi(t_node *node);
int	visit_right_redi(t_node *node);
int	visit_semi(t_node *node);
int	visit(t_node *root);

#endif
