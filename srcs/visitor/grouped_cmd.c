/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouped_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/08 21:26:13 by akeiflin         ###   ########.fr       */
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

	if (io->grp_redir)
	{
		nav = io->grp_redir;
		while (nav)
		{
			redir = (t_redir_list *)nav->data;
			if (redir->file && redir->flag & O_TRUNC)
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
	dl_push_node((t_dl_node **)&io->grp_redir, ft_calloc(sizeof(t_redir_list)));
	io->grp_redir->data = io->redir;
	io->redir = NULL;
	patch_trunc_redir(io);
}
