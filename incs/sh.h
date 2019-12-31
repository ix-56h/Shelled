/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/31 14:30:06 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CLASS_H
# define SH_CLASS_H
# include <parser.h>
# include <visitor.h>
# define PATH_MAX 256

typedef	struct	s_sh
{
	char		*input;
	t_node		*node;
	t_tokens	tok;
	t_stack		*stack;
	t_flags		f;
	char		**env;
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
char	**init_env(char **env);
char	**cpy_env(char **envp);

#endif
