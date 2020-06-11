/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:35:19 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/11 03:08:06 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "visitor_misc.h"
#include "exec.h"

void	close_all_pipe(t_io_lists io)
{
	t_pipe_list	*piped;

	piped = io.piped;
	while (piped)
	{
		close(piped->fd[0]);
		close(piped->fd[1]);
		piped = piped->next;
	}
}

int		apply_fd(t_io_lists io)
{
	int				ret;
	t_dl_node		*nav;
	t_redir_list	*redir;

	ret = 0;
	set_pipe_fd(io.piped);
	close_all_pipe(io);
	if (io.grp_io)
	{
		nav = io.grp_io;
		while (nav)
		{
			redir = ((t_io_lists *)nav->data)->redir;
			ret += set_redir_fd(redir);
			nav = nav->next;
		}
	}
	ret += set_redir_fd(io.redir);
	return (ret);
}
