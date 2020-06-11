/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_misc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:33:53 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/11 03:08:06 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_MISC_H
# define FT_VISITOR_MISC_H

# include "ast.h"
# include "tokenizer.h"
# include "job.h"

# define WRITE_END		1
# define READ_END		0

typedef struct			s_pipe_list
{
	struct s_pipe_list	*next;
	struct s_pipe_list	*prev;
	int					fd[2];
	int					used;
}						t_pipe_list;

typedef struct			s_redir_list
{
	struct s_redir_list	*next;
	struct s_redir_list	*prev;
	int					in;
	int					out;
	char				*file;
	int					flag;
}						t_redir_list;

typedef struct			s_io_lists
{
	t_redir_list		*redir;
	t_dl_node			*grp_io;
	t_pipe_list			*piped;
	char				background;
	char				*cmd;
}						t_io_lists;

int						(*g_visit_rules[TOK_POSIX_MAX])(t_node *node,
							t_io_lists io, t_job **job);

#endif
