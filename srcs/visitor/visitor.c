/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/11 04:25:38 by akeiflin         ###   ########.fr       */
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

int		visit_cmd(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	int	pid;

	if (node->tok == TOK_WORD)
	{
		restore_term();
		if ((pid = fork()) == -1)
			return (0);
		else if (pid == 0) //FILS
		{
			set_pipe_fd(piped);
			set_redir_fd(redir);
			execve(node->data, node->args, g_env);
			exit(1);
		}
		else //PARENT
		{
			close_used_pipe_fd(piped);
			if ((piped && !piped->next && piped->used == 1) || !piped)
				while (wait(NULL) > 0);
			set_term_mode();
			set_used_fd(piped);
			return (1);
		}
	}
	return (0);
}

int		visit_and_if(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped, redir))
				return (1);
		}
	}
	return (0);
}

int		visit_or_if(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
				return (1);
		else if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped, redir))
			return (1);
	}
	return (0);
}

int		visit_pipe(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	int	pipefd[2];
	
	if (node->left && node->right)
	{
		if (pipe(pipefd) == -1)
			return (0);
		dl_push_node((t_dl_node **)&piped, malloc(sizeof(t_pipe_list)), NULL);
		piped->fd[0] = pipefd[0];
		piped->fd[1] = pipefd[1];
		piped->used = 0;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped, redir))
			{
				dl_del_one((t_dl_node *)piped);
				return (1);
			}
		}
	}
	return (0);
}

int		visit_dless(t_node *node, t_pipe_list *piped, t_redir_list *redir) // <<
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
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDIN_FILENO;
		redir->out = pipefd[READ_END];
		if ((*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			dl_del_one((t_dl_node *)redir);
			return (1);
		}
	}
	return (0);
}

int		visit_dgreat(t_node *node, t_pipe_list *piped, t_redir_list *redir) // >>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_APPEND), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDOUT_FILENO;
		redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			dl_del_one((t_dl_node *)redir);
			return (1);
		}
	}
	return (0);
}

int		visit_left_redi(t_node *node, t_pipe_list *piped, t_redir_list *redir) // <
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
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDIN_FILENO;
		redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			dl_del_one((t_dl_node *)redir);
			return (1);
		}
	}
	return (0);
}

int		visit_right_redi(t_node *node, t_pipe_list *piped, t_redir_list *redir) // >
{
	int		fd;

	if (node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_WRONLY | O_TRUNC), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDOUT_FILENO;
		redir->out = fd;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
				dl_del_one((t_dl_node *)redir);
				return (1);
		}
	}
	return (0);
}

int		visit_lessand(t_node *node, t_pipe_list *piped, t_redir_list *redir) // <&
{
	//Je sais pas vraiment comment ca marche 🤔
	if (node->right && node->right->tok == TOK_WORD)
	{
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDIN_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			redir->out = -1;
		else
			redir->out = ft_atoi(node->right->data);
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
				dl_del_one((t_dl_node *)redir);
				return (1);
		}
	}
	return (0);
}

int		visit_greatand(t_node *node, t_pipe_list *piped, t_redir_list *redir) // >&
{
	if (node->right && node->right->tok == TOK_WORD)
	{
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDOUT_FILENO;
		if (ft_strcmp(node->right->data, "-") == 0)
			redir->out = -1;
		else
			redir->out = ft_atoi(node->right->data);
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
				dl_del_one((t_dl_node *)redir);
				return (1);
		}
	}
	return (0);
}

int		visit_semi(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	return (visit(node->left) + visit(node->right));
}

int		visit_lessgreat(t_node *node, t_pipe_list *piped, t_redir_list *redir) // <>
{
	int		fd;

	if (node->left && node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, (O_CREAT | O_RDWR), 0644)) == -1)
			return (0);
		dl_push_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		if (node->io != -1)
			redir->in = node->io;
		else
			redir->in = STDIN_FILENO;
		redir->out = fd;
		if ((*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			dl_del_one((t_dl_node *)redir);
			return (1);
		}
	}
	return (0);
}

int		visit(t_node *root)
{
	if (!root)
		return (1);
	if (G_VISIT_RULES[root->tok])
	{
		if ((*G_VISIT_RULES[root->tok])(root, NULL, NULL))
		{
			return (1);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}
