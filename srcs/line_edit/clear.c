/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:21:43 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/08 23:57:07 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ligne.h"

void			clear_line(t_line *line)
{
	t_pos		curpos;
	t_winsize	termsize;
	int			startline;

	termsize = get_winsize();
	curpos = get_cur_pos();
	startline = curpos.y - (line->index + line->prompt->size) / termsize.ws_col;
	cur_mov(0, startline - 1);
	term_other(TERM_CLEAR_CUR_END, 1);
}

static int		min_one(int nbr)
{
	if (nbr <= 0)
		return (1);
	return (nbr);
}

void			clear_node_line(t_dl_node *head)
{
	t_winsize	termsize;
	t_line		*tmp_line;
	int			nb_line;

	termsize = get_winsize();
	nb_line = 0;
	while (head)
	{
		tmp_line = head->data;
		if (nb_line == 0)
			nb_line += (min_one(ft_strlen(tmp_line->line))\
			+ tmp_line->prompt->size - 1) / termsize.ws_col + 1;
		else
			nb_line += (min_one(ft_strlen(tmp_line->line)) - 1)\
										/ termsize.ws_col + 1;
		head = head->next;
	}
	term_other(TERM_UP, nb_line - 1);
	term_other(TERM_STARTLINE, 1);
	term_other(TERM_CLEAR_CUR_END, 1);
}

void			free_line(t_line *line)
{
	if (line)
	{
		if (line->prompt)
		{
			if (line->prompt->str)
				free(line->prompt->str);
			free(line->prompt);
		}
		if (line->line)
			free(line->line);
		free(line);
	}
}
