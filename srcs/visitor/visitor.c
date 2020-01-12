/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/12 19:58:39 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <parser.h>
#include <visitor.h>
#include <visitor_rules.h>
#include "double_linked_list.h"
#include "ligne.h"
#include "sh.h"

int		visit_cmd(t_node *node, t_io_lists io)
{
	int	pid;

	if (node->tok == TOK_WORD)
	{
		restore_term();
		if ((pid = fork()) == -1)
			return (0);
		else if (pid == 0) //FILS
		{
			set_pipe_fd(io.piped);
			set_redir_fd(io.redir);
			execve(node->data, node->args, g_env);
			exit(1);
		}
		else //PARENT
		{
			close_used_pipe_fd(io.piped);
			if ((io.piped && !io.piped->next && io.piped->used == 1) || !io.piped)
				while (wait(NULL) > 0);
			set_term_mode();
			set_used_fd(io.piped);
			return (1);
		}
	}
	return (0);
}

int		visit_and_if(t_node *node, t_io_lists io)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, io))
				return (1);
		}
	}
	return (0);
}

int		visit_or_if(t_node *node, t_io_lists io)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
				return (1);
		else if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, io))
			return (1);
	}
	return (0);
}

int		visit_pipe(t_node *node, t_io_lists io)
{
	int	pipefd[2];
	
	if (node->left && node->right)
	{
		if (pipe(pipefd) == -1)
			return (0);
		dl_push_node((t_dl_node **)&io.piped, malloc(sizeof(t_pipe_list)), NULL);
		io.piped->fd[0] = pipefd[0];
		io.piped->fd[1] = pipefd[1];
		io.piped->used = 0;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, io))
			{
				dl_del_one((t_dl_node *)io.piped);
				return (1);
			}
		}
	}
	return (0);
}

int		visit_dless(t_node *node, t_io_lists io) // <<
{
	int		pipefd[2];
	char	*str;

	if (node->right)
	{
		str = run_heredoc(node->right->data);
		if (pipe(pipefd) == -1)
			return (0);
		write(pipefd[WRITE_END], str, ft_strlen(str));
		close(pipefd[WRITE_END]);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = pipefd[READ_END];
		if ((*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (1);
		}
	}
	return (0);
}

int		visit_dgreat(t_node *node, t_io_lists io) // >>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_APPEND), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		io.redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (1);
		}
	}
	return (0);
}

int		visit_left_redi(t_node *node, t_io_lists io) // <
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, O_RDONLY)) == -1)
		{
			ft_putstr("21sh: Aucun fichier ou dossier de ce type:");
			ft_putstr(node->right->data);
			return (0);
		}
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (1);
		}
	}
	return (0);
}

int		visit_right_redi(t_node *node, t_io_lists io) // >
{
	int		fd;

	if (node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_TRUNC), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDOUT_FILENO;
		io.redir->out = fd;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
				dl_del_one((t_dl_node *)io.redir);
				return (1);
		}
	}
	return (0);
}

int		visit_lessand(t_node *node, t_io_lists io) // <&
{
	//Je sais pas vraiment comment ca marche 🤔
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
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
				dl_del_one((t_dl_node *)io.redir);
				return (1);
		}
	}
	return (0);
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
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
				dl_del_one((t_dl_node *)io.redir);
				return (1);
		}
	}
	return (0);
}

int		visit_semi(t_node *node, t_io_lists io)
{
	return (visit(node->left) + visit(node->right));
}

int		visit_lessgreat(t_node *node, t_io_lists io) // <>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_RDWR), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&io.redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			io.redir->in = node->io;
		else
			io.redir->in = STDIN_FILENO;
		io.redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, io))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (1);
		}
	}
	return (0);
}

int		visit(t_node *root)
{
	t_io_lists io;

	if (!root)
		return (1);
	if (G_VISIT_RULES[root->tok])
	{
		io = (t_io_lists){.redir = NULL, .piped = NULL};
		if ((*G_VISIT_RULES[root->tok])(root, io))
		{
			return (1);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}
