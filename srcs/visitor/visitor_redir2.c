/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_redir2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:33:17 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 00:33:30 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"

int		visit_dless(t_node *node, t_io_lists io, int *rets)
{
	int		pipefd[2];
	char	*str;

	if (node->right && node->left)
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
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	(rets) ? *rets = 0 : 0;
	return (1);
}

int		visit_dgreat(t_node *node, t_io_lists io, int *rets)
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
		if (!(*G_VISIT_RULES[node->left->tok])(node->left, io, rets))
		{
			dl_del_one((t_dl_node *)io.redir);
			return (0);
		}
		dl_del_one((t_dl_node *)io.redir);
	}
	if (rets)
			*rets = 0;
	return (1);
}