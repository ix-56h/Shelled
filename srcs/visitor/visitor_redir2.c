/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:33:17 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/09 00:17:14 by akeiflin         ###   ########.fr       */
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
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->right && node->left)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		exec_dless(node, &io, job);
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		if (node->state == 3)
			dl_del_one(io.grp_redir);
		dl_del_one((t_dl_node *)io.redir);
	}
	return (ret);
}

/*
**	>>
*/

int		visit_dgreat(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		exec_dgreat(node, &io, job);
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		if (node->state == 3)
			dl_del_one(io.grp_redir);
		dl_del_one((t_dl_node *)io.redir);
	}
	return (ret);
}
