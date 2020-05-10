/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/08 23:39:34 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <sys/types.h>
# include <pwd.h>
# include <signal.h>
# include "ast.h"
# define FT_PATH_MAX 256
# define SHELL_NAME "42sh"

int				g_exit;
pid_t			g_shell_pgid;

char			**g_env;
char			**g_set;
char			**g_alias;

typedef	struct	s_args
{
	unsigned	ast_draw:1;
}				t_args;

typedef	struct	s_sh
{
	char			*input;
	t_node		*node;
	t_tokens	tok;
	t_stacks	stack;
	t_args		f;
}				t_sh;

typedef struct s_alias
{
	struct s_alias *next;
	char 		*data;
	int 		is;
} t_alias;

/*
**	main.c
*/

void			check_param(char **av, t_args *f);
int				init_shell(t_sh *sh, int ac, char **av, char **envp);
void			process_sh(t_sh *sh);
void			check_args(t_sh *sh, int ac, char **av);

/*
**	env.c
*/

char			**init_env(char **env);
char			**cpy_env(char **envp);
int				ft_edit_env(char **env, char *looking, char *value);
char			**add_env(char **env, char *var, char *value);
char			**del_var(char **env, char *var);

/*
**	env2.c
*/

void			free_env(char **env);
char			*get_env(char **env, char *looking);
void			add_set(char *var, char *value);

/*
**	init.c
*/

int				init_shell(t_sh *sh, int ac, char **av, char **envp);
void			re_init_sh(t_sh *sh);
void			init_set(char **av);

/*
**	utils
*/

char			*erase_char(char *str);
char			*remove_dquotes(char *w);
char			*insert_str(char *s, size_t	*pos, size_t anchor, char *str);
void			tree_draw(t_node *node);

/*
**	utils/free_sh.h
*/

void			free_sh(t_sh *sh);

/*
**	signal.c
*/

void			init_signal(void);

/*
**  alias.c
*/

char 			*add_alias(char *input, t_lifo *stack);
char  		*recursive_alias(char *alias_v, char **alias_cpy, t_lifo *stack);

char			**add_pot(char **alias, char *pot);
int 			is_alias(char *t_alias, char **cpy_alias);
char    	*get_value_by_name(char *name);
char 			*new_input(char *alias_v, char *input, int *cpt, int len_n);
void 			rm_first_space(char *input);
char    	*get_after(char *input, int cpt);
char    	*get_before(char *input, int cpt);
char 			*get_next_word(char *input, int cpt);
int 			ignore_args_n_op(char *input, int *cpt);
int  			get_len(char *input, int cpt);

#endif
