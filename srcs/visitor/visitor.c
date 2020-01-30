/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 01:18:33 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <parser.h>
#include <visitor.h>
#include <visitor_rules.h>
#include "stack.h"
#include "double_linked_list.h"
#include "ligne.h"
#include "sh.h"

int		exec_heredoc(t_fifo *stack)
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

static void	ctrl_c_handler(int lel)
{
	ft_putchar('\n');
}

int		visit_cmd(t_node *node, t_io_lists io)
{
	int	ret_value;
	int	tmp;
	int	final_ret;

	final_ret = 0;
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
			{
				tmp = wait(&ret_value);
				if (ret_value != 0)
					final_ret = ret_value;
			}
		}
		set_used_fd(io.piped);
		set_term_mode();
	}
	signal(SIGINT, SIG_DFL);
	return (final_ret);
}

int		visit_and_if(t_node *node, t_io_lists io)
{
	if (node->left && node->right)
	{
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			if (!(*G_VISIT_RULES[node->right->tok])(node->right, io))
				return (0);
		}
	}
	return (1);
}

int		visit_or_if(t_node *node, t_io_lists io)
{
	if (node->left && node->right)
	{
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io))
			return (1);
		if (!(*G_VISIT_RULES[node->right->tok])(node->right, io))
			return (0);
	}
	return (1);
}

int		visit_pipe(t_node *node, t_io_lists io)
{
	int	pipefd[2];
	
	if (node->left && node->right)
	{
		if (pipe(pipefd) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.piped, malloc(sizeof(t_pipe_list)), NULL);
		io.piped->fd[0] = pipefd[0];
		io.piped->fd[1] = pipefd[1];
		io.piped->used = 0;
		if (node->left && !(*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			if (!(*G_VISIT_RULES[node->right->tok])(node->right, io))
			{
				dl_del_one((t_dl_node *)io.piped);
				return (0);
			}
		}
	}
	return (1);
}

int		visit_semi(t_node *node, t_io_lists io)
{
	if (node->left)
		return (visit(node->left) + visit(node->right));
	return (1);
}

int		visit_dless(t_node *node, t_io_lists io) // <<
{
	int		pipefd[2];
	char	*str;

	if (node->right)
	{
		str = node->right->data;
		if (pipe(pipefd) == -1)
			return (1);
		write(pipefd[WRITE_END], str, ft_strlen(str));
		close(pipefd[WRITE_END]);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = pipefd[READ_END];
		if (node->left && !(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);
	}
	return (1);
}

int		visit_dgreat(t_node *node, t_io_lists io) // >>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_APPEND), 0644)) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		io.redir->out = fd;
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);
	}
	return (1);
}

int		visit_left_redi(t_node *node, t_io_lists io) // <
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, O_RDONLY)) == -1)
		{
			ft_vprint(3, SHELL_NAME": no such file or directory: ", node->right->data, "\n");
			return (1);
		}
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);
	}
	return (1);
}

int		visit_right_redi(t_node *node, t_io_lists io) // >
{
	int		fd;

	if (node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_TRUNC), 0644)) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		io.redir->out = fd;
		if (node->left && !(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);

	}
	return (1);
}

int		visit_lessand(t_node *node, t_io_lists io) // <&
{
	if (node->right && node->right->tok == TOK_WORD)
	{
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			io.redir->out = -1;
		else
			io.redir->out = ft_atoi(node->right->data);
		if (node->left && !(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);
	}
	return (1);
}

int		visit_greatand(t_node *node, t_io_lists io) // >&
{
	if (node->right && node->right->tok == TOK_WORD)
	{
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			io.redir->out = -1;
		else
			io.redir->out = ft_atoi(node->right->data);
		if (node->left && !(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		return (0);
	}
	return (1);
}

int		visit_lessgreat(t_node *node, t_io_lists io) // <>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_RDWR), 0644)) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io))
			dl_del_one((t_dl_node *)io.redir);
		
		return (0);
	}
	return (1);
}

int		visit(t_node *root)
{
	t_io_lists io;

	if (!root)
		return (0);
	if (G_VISIT_RULES[root->tok])
	{
		io = (t_io_lists){.redir = NULL, .piped = NULL};
		if (!(*G_VISIT_RULES[root->tok])(root, io))
		{
			return (0);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (1);
}
