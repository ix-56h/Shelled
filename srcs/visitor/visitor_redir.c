/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:59:58 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/19 18:16:21 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"

/*
**	<>
*/

int		visit_lessgreat(t_node *node, t_io_lists io, t_job **job)
{
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
