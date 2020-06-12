/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_assign2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/06/11 17:50:30 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"
#include "builtins.h"
#include "expansions.h"
#include "ft_printf.h"

int		visit_assign_redir(t_node *node, t_io_lists *io, t_job **job)
{
	if (node->left->tok == TOK_ASSIGNMENT_WORD)
	{
		if (!(*g_visit_rules[node->left->tok])(node->left, *io, job))
		{
			dl_del_one((t_dl_node *)io->redir);
			return (0);
		}
		if (!(*g_visit_rules[node->left->left->tok])(node->left->left
		, *io, job))
		{
			restore_env_back(node->left);
			dl_del_one((t_dl_node *)io->redir);
			return (0);
		}
	}
	return (1);
}

void	visit_assign_pipe(t_node *node, t_io_lists *io, t_job **job, int *pipe)
{
	if ((*g_visit_rules[node->left->tok])(node->left, *io, job))
	{
		close(pipe[WRITE_END]);
		set_used_fd(io->piped);
	}
	if (node->left->left
		&& (*g_visit_rules[node->left->left->tok])(node->left->left, *io, job))
	{
		close(pipe[WRITE_END]);
		set_used_fd(io->piped);
	}
}
