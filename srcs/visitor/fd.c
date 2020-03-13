/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 23:06:50 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/13 01:46:58 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "visitor_misc.h"

int		set_pipe_fd(t_pipe_list *piped)
{
	if (piped)
	{
		if (piped->used == 1)
		{
			if (dup2(piped->fd[READ_END], STDIN_FILENO) == -1)
				return (EXIT_FAILURE);
			close(piped->fd[READ_END]);
		}
		if (!piped->prev && piped->used != 1)
		{
			if (dup2(piped->fd[WRITE_END], STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
			close(piped->fd[WRITE_END]);
		}
		else if (piped->next)
		{
			if (dup2(piped->next->fd[WRITE_END], STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
			close(piped->next->fd[WRITE_END]);
		}
	}
	return (EXIT_SUCCESS);
}

int		close_used_pipe_fd(t_pipe_list *piped)
{
	if (piped)
	{
		if (piped->used == 1)
		{
			close(piped->fd[READ_END]);
			piped->fd[READ_END] = -2;
		}
		if (!piped->prev && piped->used != 1)
		{
			close(piped->fd[WRITE_END]);
			piped->fd[WRITE_END] = -2;
		}
		else if (piped->next)
		{
			close(piped->next->fd[WRITE_END]);
			piped->next->fd[WRITE_END] = -2;
		}
	}
	return (EXIT_SUCCESS);
}

int		set_used_fd(t_pipe_list *piped)
{
	if (piped)
	{
		if (!piped->prev && piped->used != 1)
			piped->used = 1;
		else if (piped->next)
			piped->next->used = 1;
	}
	return (EXIT_SUCCESS);
}

int		set_redir_fd(t_redir_list *redir)
{
	if (redir)
	{
		while (redir)
		{
			if (redir->out == -1)
			{
				close(redir->in);
				redir->in = -2;
			}
			else if (dup2(redir->out, redir->in) == -1)
				return (EXIT_FAILURE);
			redir = redir->next;
		}
	}
	return (EXIT_SUCCESS);
}
