/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_greatand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:29:41 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/19 18:36:42 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "exec.h"

int	exec_great_and(t_node *node, t_io_lists *io, t_job **job)
{
	(void)job;
	if (!ft_isalldigit(node->right->data)
			&& ft_strcmp(node->right->data, "-") != 0)
		return (err_exec(node->right->data, ERR_REDIR));
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	if (node->io != -1)
		io->redir->in = node->io;
	else
		io->redir->in = STDOUT_FILENO;
	if (ft_strcmp(node->right->data, "-") == 0)
		io->redir->out = -1;
	else
		io->redir->out = ft_atoi(node->right->data);
	return (0);
}
