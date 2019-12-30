/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 13:39:02 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/30 18:57:55 by niguinti         ###   ########.fr       */
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



/*
**	env.c
*/
char	**init_env(char **env);

#endif
