/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_dless.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:33:37 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/19 18:07:36 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "builtins.h"
#include "exec.h"

int	exec_dless(t_node *node, t_io_lists *io, t_job **job)
{
	int		pipefd[2];
	char	*str;

	(void)job;
	str = node->right->data;
	if (pipe(pipefd) == -1)
		return (1);
	write(pipefd[WRITE_END], str, ft_strlen(str));
	close(pipefd[WRITE_END]);
	dl_push_node((t_dl_node **)&io->redir, ft_calloc(sizeof(t_redir_list)));
	io->redir->in = (node->io != -1 ? node->io : STDIN_FILENO);
	io->redir->out = pipefd[READ_END];
	return (0);
}
