/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/05/11 12:58:43 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <sys/types.h>
# include <pwd.h>
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
	char		*input;
	t_node		*node;
	t_tokens	tok;
	t_stacks	stack;
	t_args		f;
}				t_sh;

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
void			oprhaned_jobs(void);

/*
** shell_var.c
*/

void			get_special_param(char ***w);

/*
**  alias.c
*/

char			*add_alias(char *input, t_lifo *stack);
char			*recursive_alias(char *alias_v, char **alias_cpy, t_lifo *stack);

int				is_alias(char *t_alias, char **cpy_alias);
char			*get_value_by_name(char *name);
char			*test_alias(char *alias_n, t_lifo *stac);

/*  print  */
char			*print_new_input(char **pot_alias, int *toktype, t_lifo *stack);
char			*join_new_input(char *data, char *new_input, int *i);
void			print_with_alias(char *data, char **alias_v, int *i);
char			*print_recursive_alias(char **alias_cpy, char **save_alias\
										, char **pot_alias, t_lifo *sta);

/*  free   */
void			free_alias(char **alias);
char			*free_recursive_launch(char **pot_alias, char **save_alias\
										, char **alias_cpy, char *new_input);
char			*free_recursive(char *input_s, char **alias_cpy, char *alias_v);
int				f_s(char **save_alias);
void			reset_token(t_tokens token, int *is_multi);

/*   tools */
char			**cpy_alias(char **alias);
char			**alloc_pot(char *data, char **pot_alias, int *i);
int				*alloc_toktype(int *toktype, int *is_multi, char **pot, t_tokens token);
char			**add_pot(char **alias, char *pot);

#endif
