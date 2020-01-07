/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 20:26:34 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/07 18:27:42 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_LINKED_LIST
# define DOUBLE_LINKED_LIST

typedef struct  s_dl_node
{
    struct s_dl_node   *next;
    struct s_dl_node   *prev;
    void            *data;
}				t_dl_node;

int				dl_push(t_dl_node** head_ref, void *new_data);
int				dl_append(t_dl_node** head_ref, void *new_data);
int             dl_push_node(t_dl_node** head_ref, t_dl_node *new_node, void *new_data);
int				dl_insert_before(t_dl_node* head_ref, t_dl_node* next_dl_node,
						    void *new_data);
t_dl_node       *dl_find_data(t_dl_node *haystack, void *needle);
t_dl_node       *dl_get_last(t_dl_node *head);
t_dl_node       *dl_get_head(t_dl_node *node);
void        	dl_del_one(t_dl_node *node);
void        	dl_del_one_with_data(t_dl_node *node, void (*free_fonc)());
void			dl_free_list(t_dl_node *head);
void            dl_free_whith_content(t_dl_node *head, void (*free_fonc)());
#endif
