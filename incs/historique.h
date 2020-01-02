/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:25:37 by akeiflin          #+#    #+#             */
/*   Updated: 2019/12/31 00:27:48 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORIQUE_H
# define HISTORIQUE_H
# include "ligne.h"
# include "double_linked_list.h"

typedef t_dl_node t_historic;

void			add_historic(t_dl_node *command);
t_dl_node			*historic_get_next(void);
t_dl_node			*historic_get_last(void);
void			historic_reset(void);
int				historic_on_use(int act);
void			free_historic();
#endif