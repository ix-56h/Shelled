#ifndef DOUBLE_LINKED_LIST
# define DOUBLE_LINKED_LIST

typedef struct  s_dl_node
{
    void            *data;
    struct s_dl_node   *next;
    struct s_dl_node   *prev;
}				t_dl_node;

int				dl_push(t_dl_node** head_ref, void *new_data);
int				dl_append(t_dl_node** head_ref, void *new_data);
int				dl_insert_before(t_dl_node* head_ref, t_dl_node* next_dl_node,
						    void *new_data);
t_dl_node			*dl_find_data(t_dl_node *haystack, void *needle);
t_dl_node			*dl_get_last(t_dl_node *head);
t_dl_node          *dl_get_head(t_dl_node *node);
void			dl_free_list(t_dl_node *head);
void            dl_free_whith_content(t_dl_node *head, void (*free_fonc)());
#endif