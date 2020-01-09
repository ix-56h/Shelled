/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/09 17:00:47 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CLASS_H
# define SH_CLASS_H
# include <sys/types.h>
# include <pwd.h>
# include <parser.h>
# include <visitor.h>
# define PATH_MAX 256

char	**g_env;

typedef	struct	s_sh
{
	char		*input;
	t_node		*node;
	t_tokens	tok;
	t_stack		*stack;
	t_flags		f;
}				t_sh;


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

#endif
