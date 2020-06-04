/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:33:17 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/02 00:25:07 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"
#include "exec.h"
#include "visitor.h"

/*
**	<<
*/

int		visit_dless(t_node *node, t_io_lists io, t_job **job)
{
	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->right && node->left)
	{
		exec_dless(node, &io, job);
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
**	>>
*/

int		visit_dgreat(t_node *node, t_io_lists io, t_job **job)
{
	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		exec_dgreat(node, &io, job);
		if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	return (1);
}
