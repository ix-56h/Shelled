/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 03:45:11 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"
#include "visitor_rules.h"

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
			}
			else
				err = 1;
		}
		fifo_delete(stack);
	}
	return ((err) ? 0 : 1);
}

static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}

int				visit_cmd(t_node *node, t_io_lists io, int *rets)
{
	int	ret_value;
	int	tmp;

	ret_value = 1;
	signal(SIGINT, ctrl_c_handler);
	if (node->tok == TOK_WORD)
	{
		restore_term();
		exec_cmd(node, NULL, io);
		if ((io.piped && !io.piped->next && io.piped->used == 1) || !io.piped)
		{
			tmp = 1;
			while (tmp > 0)
				tmp = wait(&ret_value);
			if (rets)
				*rets = ret_value;
		}
		set_used_fd(io.piped);
		set_term_mode();
	}
	signal(SIGINT, SIG_DFL);
	return (0);
}

int				visit(t_node *root)
{
	t_io_lists io;

	if (!root)
		return (0);
	if (g_visit_rules[root->tok])
	{
		io = (t_io_lists){.redir = NULL, .piped = NULL};
		if (!(*g_visit_rules[root->tok])(root, io, NULL))
			return (0);
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (1);
}
