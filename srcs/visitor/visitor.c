/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/03 03:20:51 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "ligne.h"
#include "visitor.h"
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

int				visit(t_node *root, t_job **job)
{
	t_io_lists io;
	
	if (!root)
		return (0);
	if (g_visit_rules[root->tok])
	{
		io = (t_io_lists){.redir = NULL, .piped = NULL};
		dl_append_node(job, ft_calloc(sizeof(t_process)));
		t_job * last_job = dl_get_last(*job);
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


char			*substitution_wrapper(t_node *root)
{
	int		pipefd[2];
	char	*ret;
	int		stdout_save;
	char	buff[BUFFSIZE + 1];
	int		pid;
	t_job	*tmp;

	tmp = NULL;
	if (pipe(pipefd) != -1)
	{
		stdout_save = dup(STDOUT_FILENO);
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
		close(pipefd[WRITE_END]);
		if ((pid = fork()) == -1)
		{
			close(pipefd[READ_END]);
			dup2(stdout_save, STDOUT_FILENO);
			return (NULL);
		}
		else if (pid == 0)
		{
			close(pipefd[READ_END]);
			visit(root, &tmp);
			exit(0);
		}
		dup2(stdout_save, STDOUT_FILENO);
		wait(NULL);
		ft_bzero(buff, sizeof(char) * (BUFFSIZE + 1));
		ret = ft_strdup("");
		while (read(pipefd[READ_END], buff, BUFFSIZE) > 0)
		{
			ret = ft_strjoinf(ret, buff, 1);
			ft_bzero(buff, sizeof(char) * (BUFFSIZE + 1));
		}
		close(pipefd[READ_END]);
		return (ret);
	}
	return (NULL);
}