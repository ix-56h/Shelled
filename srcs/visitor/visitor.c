/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/12 02:59:15 by akeiflin         ###   ########.fr       */
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
}

void			wait_and_ret(int tmp, t_io_lists io, int *rets)
{
	int	ret_value;

	ret_value = 1;
	if (rets)
		*rets = tmp;
	if ((io.piped && !io.piped->next && io.piped->used == 1) || !io.piped)
	{
		tmp = 1;
		while (tmp > 0)
			tmp = wait(&ret_value);
		if (ret_value == 2)
			ft_putchar('\n');
		if (rets && *rets == 0)
			*rets = ret_value;
	}
}

int				visit_cmd(t_node *node, t_io_lists io, int *rets)
{
	int	ctrlc;

	ctrlc = 0;
	signal(SIGINT, ctrl_c_handler);
	if (node->tok == TOK_WORD)
	{
		restore_term();
		wait_and_ret(exec_cmd(node, NULL, io), io, rets);
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
	{
		ft_putstr("21sh: no visit function for '");
		ft_putstr(root->data);
		ft_putstr("'\n");
	}
	return (1);
}
