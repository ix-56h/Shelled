/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/11 16:36:05 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include "visitor.h"
#include "exec.h"

static void		patch_trunc_redir(t_io_lists *io)
{
	t_dl_node		*nav;
	t_redir_list	*redir;
	struct stat		buf;

	if (io->grp_io)
	{
		nav = io->grp_io;
		while (nav)
		{
			redir = ((t_io_lists *)nav->data)->redir;
			if (redir && redir->file && redir->flag & O_TRUNC)
			{
				if (stat(redir->file, &buf) == 0)
				{
					if (!S_ISFIFO(buf.st_mode))
					{
						close(open(redir->file, redir->flag));
						redir->flag = redir->flag ^ O_TRUNC;
						redir->flag = redir->flag | O_APPEND;
					}
				}
			}
			nav = nav->next;
		}
	}
}

void			grp_cmd_wrapper(t_io_lists *io)
{
	dl_push((t_dl_node **)&io->grp_io, ft_calloc(sizeof(t_io_lists)));
	((t_io_lists *)io->grp_io->data)->redir = io->redir;
	((t_io_lists *)io->grp_io->data)->background = io->background;
	io->redir = NULL;
	io->background = 0;
	patch_trunc_redir(io);
}
