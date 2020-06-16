/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:59:58 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/16 03:07:11 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"
#include "exec.h"
#include "expansions.h"

/*
**	<
*/

int		visit_left_redi(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		node->right->data = expand_word(node->right->data);
		exec_left_redi(node, &io, job);
		if (!visit_assign_redir(node, &io, job))
		{
			if (node->state == 3)
				dl_del_one_with_data(io.grp_io, free);
			return (0);
		}
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		dl_del_one((t_dl_node *)io.redir);
		if (node->state == 3)
			dl_del_one_with_data(io.grp_io, free);
	}
	return (ret);
}

/*
**	>
*/

int		visit_right_redi(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		node->right->data = expand_word(node->right->data);
		exec_right_redi(node, &io, job);
		if (!visit_assign_redir(node, &io, job))
		{
			if (node->state == 3)
				dl_del_one_with_data(io.grp_io, free);
			return (0);
		}
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		dl_del_one((t_dl_node *)io.redir);
		if (node->state == 3)
			dl_del_one_with_data(io.grp_io, free);
	}
	return (ret);
}

/*
**	<&
*/

int		visit_lessand(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		node->right->data = expand_word(node->right->data);
		exec_less_and(node, &io, job);
		if (!visit_assign_redir(node, &io, job))
		{
			if (node->state == 3)
				dl_del_one_with_data(io.grp_io, free);
			return (0);
		}
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		dl_del_one((t_dl_node *)io.redir);
		if (node->state == 3)
			dl_del_one_with_data(io.grp_io, free);
	}
	return (ret);
}

/*
**	>&
*/

int		visit_greatand(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		node->right->data = expand_word(node->right->data);
		exec_great_and(node, &io, job);
		if (!visit_assign_redir(node, &io, job))
		{
			if (node->state == 3)
				dl_del_one_with_data(io.grp_io, free);
			return (0);
		}
		ret = (*g_visit_rules[node->left->tok])(node->left, io, job);
		if (node->state == 3)
			dl_del_one_with_data(io.grp_io, free);
		dl_del_one((t_dl_node *)io.redir);
	}
	return (ret);
}
