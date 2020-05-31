/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/05/22 18:23:39 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "ligne.h"
#include <expansions.h>
#include "visitor.h"
#include "visitor_rules.h"
#include "sh.h"
#include "parser.h"

int				exec_heredoc(t_fifo *stack)
{
	t_node	*node;
	char	*str;
	int		err;

	err = 0;
	while (!fifo_empty(stack))
	{
		node = fifo_peek(stack);
		if (node->right)
		{
			if ((str = run_heredoc(node->right->data)))
			{
				free(node->right->data);
				node->right->data = str;
				node->right->tok = TOK_HERE;
			}
			else
				err = 1;
		}
		fifo_delete(stack);
	}
	return ((err) ? 0 : 1);
}

int				visit_cmd(t_node *node, t_io_lists io, t_job **job)
{
	exec_command(node, &io, job);
	return (0);
}

int				visit_background(t_node *node, t_io_lists io, t_job **job)
{
	io.background = 1;
	if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		return (0);
	return (1);
}

int				visit(t_node *root, t_job **job, char *cmd)
{
	t_io_lists	io;
	t_job		*last_job;

	if (!root)
		return (0);
	root->data = expand_word(root->data);
	if (g_visit_rules[root->tok])
	{
		io = (t_io_lists){NULL, NULL, 0, cmd};
		last_job = create_job();
		if (!(*g_visit_rules[root->tok])(root, io, &last_job))
			return (0);
	}
	else
	{
		ft_putstr("42sh: no visit function for '");
		ft_putstr(root->data);
		ft_putstr("'\n");
	}
	return (1);
}
