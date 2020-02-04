/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:25:37 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/04 03:44:54 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORIQUE_H
# define HISTORIQUE_H
# include "ligne.h"
# include "double_linked_list.h"

typedef t_dl_node	t_historic;

int					historic_on_use(int act);
t_historic			**get_historic(void);
void				add_historic(t_dl_node *command);
t_dl_node			*historic_get_next(void);
t_dl_node			*historic_get_last(void);
void				historic_reset(void);
void				free_historic(void);
t_historic			*controller_next(t_historic **historic);
t_historic			*controller_prev(t_historic **historic\
									, t_historic *null_node);
t_historic			*controller_reset(t_historic **historic\
									, t_historic **null_node);
t_historic			*historic_controller(char act);
void				trim_and_add_historic(t_dl_node **head);
#endif
