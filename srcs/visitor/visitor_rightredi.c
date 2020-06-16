/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_rightredi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:38:07 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/16 02:43:59 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "builtins.h"
#include "exec.h"

int	exec_right_redi(t_node *node, t_io_lists *io, t_job **job)
{
	int	fd;

	(void)job;
	fd = -10;
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	io->redir->file = node->right->data;
	io->redir->flag = (O_CREAT | O_WRONLY | O_TRUNC);
	if (node->io != -1)
		io->redir->in = node->io;
	else
		io->redir->in = STDOUT_FILENO;
	io->redir->out = fd;
	return (0);
}
