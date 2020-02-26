/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_leftredi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:26:18 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/24 21:42:12 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include "builtins.h"
#include "exec.h"

int	exec_left_redi(t_node *node, t_io_lists *io, t_job **job)
{
	int	fd;

	if ((fd = open(node->right->data, O_RDONLY)) == -1)
		return (err_exec(node->right->data, ERR_NO_FILE));
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	io->redir->in = (node->io != -1 ? node->io : STDIN_FILENO);
	io->redir->out = fd;
	return (0);	
}