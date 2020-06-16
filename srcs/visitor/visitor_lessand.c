/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_lessand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:52:04 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/16 03:00:58 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "libft.h"
#include "job.h"
#include "visitor_misc.h"
#include "exec.h"

int	exec_less_and(t_node *node, t_io_lists *io, t_job **job)
{
	(void)job;
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	if (node->io != -1)
		io->redir->in = node->io;
	else
		io->redir->in = STDIN_FILENO;
	if (ft_strcmp(node->right->data, "-") == 0)
		io->redir->out = -1;
	else if (ft_isalldigit(node->right->data))
		io->redir->out = ft_atoi(node->right->data);
	else
	{
		io->redir->file = node->right->data;
		io->redir->flag = O_RDONLY;
		io->redir->out = -10;
	}
	return (0);
}
