/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 07:02:55 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CLASS_H
# define SH_CLASS_H
# include <sys/types.h>
# include <pwd.h>
# include "ast.h"
# define FT_PATH_MAX 256
# define SHELL_NAME "21sh"

int	g_exit;

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

char	**g_env;

/*
**	main.c
*/

void		check_param(char **av, t_flags *f);
void		free_sh(t_sh *sh);
int			init_shell(t_sh *sh, int ac, char **av, char **envp);
void		tree_draw(t_node *node, t_flags f);

/*
**	env.c
*/

char		**init_env(char **env);
char		**cpy_env(char **envp);
int			ft_edit_env(char **env, char *looking, char *value);
char		**add_env(char **env, char *var, char *value);
char		**del_var(char **env, char *var);
void		free_env(char **env);
char		*get_env(char **env, char *looking);

/*
**	utils
*/

char	*erase_char(char *str);
char	*remove_dquotes(char *w);
char	*insert_str(char *s, size_t	*pos, size_t anchor, char *str);

#endif
