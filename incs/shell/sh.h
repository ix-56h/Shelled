/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/07 15:00:35 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include <sys/types.h>
# include <pwd.h>
# include "ast.h"
# define FT_PATH_MAX 256
# define SHELL_NAME "21sh"

int				g_exit;
char			**g_env;

typedef	struct	s_flags
{
	unsigned	ast_draw:1;
}				t_flags;

typedef	struct	s_sh
{
	char		*input;
	t_node		*node;
	t_tokens	tok;
	t_stacks	stack;
	t_flags		f;
}				t_sh;

/*
**	main.c
*/

void			check_param(char **av, t_flags *f);
int				init_shell(t_sh *sh, int ac, char **av, char **envp);
void			tree_draw(t_node *node, t_flags f);
void			process_sh(t_sh *sh);

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

/*
**	init.c
*/

int				init_shell(t_sh *sh, int ac, char **av, char **envp);
void			re_init_sh(t_sh *sh);

/*
**	utils
*/

char			*erase_char(char *str);
char			*remove_dquotes(char *w);
char			*insert_str(char *s, size_t	*pos, size_t anchor, char *str);

/*
**	utils/free_sh.h
*/

void			free_sh(t_sh *sh);
#endif
