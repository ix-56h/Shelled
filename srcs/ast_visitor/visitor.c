/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/02 19:15:30 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <parser.h>
#include <visitor.h>
#include "visitor_rules.h"
#include "double_linked_list.h"

int	save_fd(int	savedfd[3])
{
	if ((savedfd[0] = dup(STDIN_FILENO)) == -1)
		return (EXIT_FAILURE);
	if ((savedfd[1] = dup(STDOUT_FILENO)) == -1)
		return (EXIT_FAILURE);
	if ((savedfd[2] = dup(STDERR_FILENO)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	restore_fd(int savedfd[3])
{
	if (dup2(savedfd[0], STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (dup2(savedfd[1], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	if (dup2(savedfd[2], STDERR_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		set_pipe_fd(t_pipe_list *piped)
{
	if (piped->used == 1)
	{
		//printf( "With stdin %i\n", piped->fd[READ_END]);
		if (dup2(piped->fd[READ_END], 0) == -1)
			return (EXIT_FAILURE);
	}
	if (!piped->prev && piped->used != 1)
	{
		//printf( "With stdout %i\n", piped->fd[WRITE_END]);
		if (dup2(piped->fd[WRITE_END], 1) == -1)
			return (EXIT_FAILURE);
		piped->used = 1;
	}
	else if (piped->next)
	{
		//printf( "With stdout %i\n", piped->next->fd[WRITE_END]);
		if (dup2(piped->next->fd[WRITE_END], 1) == -1)
			return (EXIT_FAILURE); 
		piped->next->used = 1;
	}
	return (EXIT_SUCCESS);
}

int		set_redir_fd(t_redir_list *redir)
{
	while (redir)
	{
		if (dup2(redir->out, redir->in) == 1)
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	return (1);
}

int		visit_cmd(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	int	pid;
	int	savedfd[3];

	if (node->tok == TOK_WORD)
	{
		save_fd(savedfd);
		printf( "Executing : %s\n", node->data);
		if (redir)
			set_redir_fd(redir);
		if (piped)
			set_pipe_fd(piped);
		if ((pid = fork()) == -1)
			return (0);
		else if (pid == 0) //FILS
		{
			if (piped)
				close(piped->fd[READ_END]);
			execve(node->data, node->args, NULL);
			exit(1);
		}
		else //PARENT
		{
			if (piped)
				close(piped->fd[WRITE_END]);
			if (!piped  || (piped && !piped->next))
				wait(NULL);
			restore_fd(savedfd);
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
		printf("New pipe fd: %i, %i\n", pipefd[WRITE_END], pipefd[READ_END]);
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped, redir))
			{
				dl_free_one((t_dl_node *)piped);
				return (1);
			}
		}
	}
	return (0);
}

int		visit_dless(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
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

int		visit_dgreat(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	int		fd;

	if (node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, O_CREAT | O_WRONLY | O_APPEND, 0744)) == -1)
			return (0);
		dl_append_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		redir->in = node->io;
		redir->out = fd;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
			dl_free_one((t_dl_node *)redir);
			return (1);
		}
	}
	return (0);
}

int		visit_left_redi(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_right_redi(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	int		fd;

	if (node->right && node->right->tok == TOK_WORD)
	{
		if ((fd = open(node->right->data, O_CREAT | O_WRONLY | O_TRUNC, 0744)) == -1)
			return (0);
		dl_append_node((t_dl_node **)&redir, malloc(sizeof(t_redir_list)), NULL);
		redir->in = node->io;
		redir->out = fd;
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped, redir))
		{
				dl_free_one((t_dl_node *)redir);
				return (1);
		}
	}
	return (0);
}

int		visit_lessand(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_greatand(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_semi(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	return (visit(node->left) + visit(node->right));
}

int		visit_lessgreat(t_node *node, t_pipe_list *piped, t_redir_list *redir)
{
	/*
	** Function for 42sh
	*/
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
			printf("wahouh\n");
			return (1);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}
