/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:59:58 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/02 00:20:42 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"

/*
**	<>
*/

int		visit_lessgreat(t_node *node, t_io_lists io, t_job **job)
{
	/*int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_RDWR), 0644)) == -1)
			return (err_exec(node->right->data, ERR_PATH_ACCES));
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)));
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}*/
	(void)node;
	(void)io;
	(void)job;
	return (1);
}

/*
**	<
*/

int		visit_left_redi(t_node *node, t_io_lists io, t_job **job)
{
	

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		exec_left_redi(node, &io, job);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	return (1);
}

/*
**	>
*/

int		visit_right_redi(t_node *node, t_io_lists io, t_job **job)
{
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		exec_right_redi(node, &io, job);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	return (1);
}

/*
**	<&
*/

int		visit_lessand(t_node *node, t_io_lists io, t_job **job)
{
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		exec_less_and(node, &io, job);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	return (1);
}

/*
**	>&
*/

int		visit_greatand(t_node *node, t_io_lists io, t_job **job)
{
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		exec_great_and(node, &io, job);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	return (1);
}
