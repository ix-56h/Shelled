/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/01 20:45:56 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <parser.h>
#include <visitor.h>
#include <visitor_rules.h>
#include "double_linked_list.h"

void	save_fd(int	savedfd[3])
{
	savedfd[0] = dup(STDIN_FILENO);
	savedfd[1] = dup(STDOUT_FILENO);
	savedfd[2] = dup(STDERR_FILENO);
}

void	restore_fd(int savedfd[3])
{
	dup2(savedfd[0], STDIN_FILENO);
	dup2(savedfd[1], STDOUT_FILENO);
	dup2(savedfd[2], STDERR_FILENO);
}

int		visit_cmd(t_node *node, t_pipe_list *piped)
{
	int	pid;
	int	savedfd[3];

	if (node->tok == TOK_WORD)
	{
		save_fd(savedfd);
		printf( "Executing : %s\n", node->data);
		if (piped)
		{
			if (piped->used == 1)
			{
				printf( "With stdin %i\n", piped->fd[1]);
				dup2(piped->fd[1], 0);
			}
			if (!piped->prev && piped->used != 1)
			{
				printf( "With stdout %i\n", piped->fd[0]);
				piped->used = 1;
				dup2(piped->fd[0], 1);
			}
			else if (piped->next)
			{
				printf( "With stdout %i\n", piped->next->fd[0]);
				piped->next->used = 1;
				dup2(piped->next->fd[0], 1);
			}
		}
		if ((pid = fork()) == -1)
			return (0);
		else if (pid == 0) //FILS
		{

			execve(node->data, node->args, NULL);
			wait(NULL);
			exit(1);
		}
		else //PARENT
		{
			restore_fd(savedfd);
			return (1);
		}
	}
	return (0);
}

int		visit_and_if(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
				return (1);
		}
	}
	return (0);
}

int		visit_or_if(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
				return (1);
		else if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
			return (1);
	}
	return (0);
}

int		visit_pipe(t_node *node, t_pipe_list *piped)
{
	/*if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
				return (1);
		}
	}
	return (0);*/
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
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
			{
				dl_free_one((t_dl_node *)piped);
				return (1);
			}
		}
	}
	return (0);
}

int		visit_dless(t_node *node, t_pipe_list *piped)
{
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
				return (1);
		}
	}
	return (0);
}

int		visit_dgreat(t_node *node, t_pipe_list *piped)
{
	if (node->left && node->right)
	{
		if (G_VISIT_RULES[node->left->tok] && (*G_VISIT_RULES[node->left->tok])(node->left, piped))
		{
			if (G_VISIT_RULES[node->right->tok] && (*G_VISIT_RULES[node->right->tok])(node->right, piped))
				return (1);
		}
	}
	return (0);
}

int		visit_left_redi(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_right_redi(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_lessand(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_greatand(t_node *node, t_pipe_list *piped)
{
	/*
	** Function for 42sh
	*/
	return (0);
}

int		visit_semi(t_node *node, t_pipe_list *piped)
{
	return (visit(node->left) + visit(node->right));
}

int		visit_lessgreat(t_node *node, t_pipe_list *piped)
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
		if ((*G_VISIT_RULES[root->tok])(root, NULL))
		{
			printf("wahouh\n");
			return (1);
		}
	}
	else
		printf("21sh: no visit function for '%s'\n", root->data);
	return (0);
}
