/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:59:58 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/10 16:17:00 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "builtins.h"
#include "exec.h"

/*
**	<>
*/

int		visit_lessgreat(t_node *node, t_io_lists io, int *rets)
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_RDWR), 0644)) == -1)
			return (err_exec(node->right->data, ERR_REDIR));
		dl_push_node((t_dl_node **)&io.redir\
						, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if (!(*g_visit_rules[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	if (rets)
		*rets = 0;
	return (1);
}

/*
**	<
*/

int		visit_left_redi(t_node *node, t_io_lists io, int *rets)
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, O_RDONLY)) == -1)
		{
			ft_vprint(3, SHELL_NAME": no such file or directory: "\
						, node->right->data, "\n");
			return (1);
		}
		dl_push_node((t_dl_node **)&io.redir\
						, malloc(sizeof(t_redir_list)), NULL);
		io.redir->in = (node->io != -1 ? node->io : STDIN_FILENO);
		io.redir->out = fd;
		if (!(*g_visit_rules[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	rets ? *rets = 0 : 0;
	return (1);
}

/*
**	>
*/

int		visit_right_redi(t_node *node, t_io_lists io, int *rets)
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data\
						, (O_CREAT | O_WRONLY | O_TRUNC), 0644)) == -1)
			return (err_exec(node->right->data, ERR_REDIR));
		dl_push_node((t_dl_node **)&io.redir\
					, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		io.redir->out = fd;
		if (!(*g_visit_rules[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	if (rets)
		*rets = 0;
	return (1);
}

/*
**	<&
*/

int		visit_lessand(t_node *node, t_io_lists io, int *rets)
{
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (ft_isallnum(node->right->data)
				|| ft_strcmp(node->right->data, "-") == 0)
			return (err_exec(node->right->data, ERR_REDIR));
		dl_push_node((t_dl_node **)&io.redir\
						, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			io.redir->out = -1;
		else
			io.redir->out = ft_atoi(node->right->data);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	if (rets)
		*rets = 0;
	return (1);
}

/*
**	>&
*/

int		visit_greatand(t_node *node, t_io_lists io, int *rets)
{
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (ft_isallnum(node->right->data)
				|| ft_strcmp(node->right->data, "-") == 0)
			return (err_exec(node->right->data, ERR_REDIR));
		dl_push_node((t_dl_node **)&io.redir\
					, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			io.redir->out = -1;
		else
			io.redir->out = ft_atoi(node->right->data);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	if (rets)
		*rets = 0;
	return (1);
}
