/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:35:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 03:32:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"

int		visit_and_if(t_node *node, t_io_lists io, int *rets)
{
	int ret;

	if (node->left && node->right)
	{
		ret = -1;
		(*G_VISIT_RULES[node->left->tok])(node->left, io, &ret);
		if (ret == 0)
			if (!(*G_VISIT_RULES[node->right->tok])(node->right, io, rets))
				return (0);
	}
	return (1);
}

int		visit_or_if(t_node *node, t_io_lists io, int *rets)
{
	int ret;

	if (node->left && node->right)
	{
		ret = 0;
		(*G_VISIT_RULES[node->left->tok])(node->left, io, &ret);
		if (ret != 0)
			if (!(*G_VISIT_RULES[node->right->tok])(node->right, io, rets))
				return (0);
	}
	return (1);
}

int		visit_pipe(t_node *node, t_io_lists io, int *rets)
{
	int	pipefd[2];

	if (node->left && node->right)
	{
		if (pipe(pipefd) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.piped\
						, malloc(sizeof(t_pipe_list)), NULL);
		io.piped->fd[0] = pipefd[0];
		io.piped->fd[1] = pipefd[1];
		io.piped->used = 0;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, io, rets))
		{
			close(pipefd[WRITE_END]);
			set_used_fd(io.piped);
		}
		if (!(*G_VISIT_RULES[node->right->tok])(node->right, io, rets))
		{
			dl_del_one((t_dl_node *)io.piped);
			return (0);
		}
		dl_del_one((t_dl_node *)io.piped);
	}
	return (1);
}

int		visit_semi(t_node *node, t_io_lists io, int *rets)
{
	(void)io;
	(void)rets;
	return (visit(node->left) + visit(node->right));
}
