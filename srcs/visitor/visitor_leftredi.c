/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_leftredi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:26:18 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/16 02:59:06 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "builtins.h"
#include "exec.h"

int	exec_left_redi(t_node *node, t_io_lists *io, t_job **job)
{
	int	fd;

	(void)job;
	fd = -10;
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	io->redir->file = node->right->data;
	io->redir->flag = O_RDONLY;
	io->redir->in = (node->io != -1 ? node->io : STDIN_FILENO);
	io->redir->out = fd;
	return (0);
}
