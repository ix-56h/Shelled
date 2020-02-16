/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:06:53 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/16 15:47:55 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ligne.h"

void	move_cur_on_newline(t_line *line)
{
	t_winsize	winsize;

	winsize = get_winsize();
	if ((line->index + line->prompt->size) % winsize.ws_col == 0)
	{
		term_other(TERM_DOWN, 1);
		if (get_env(g_env, "LC_TERMINAL") &&
			ft_strcmp(get_env(g_env, "LC_TERMINAL"), "iTerm2") == 0)
			term_other(TERM_STARTLINE, 1);
		else
			term_other(TERM_LEFT, winsize.ws_col - 1);
	}
}

void	move_cur_on_last_line(t_dl_node *head)
{
	if (head)
	{
		while ((head = head->next))
		{
			cur_move_to_index(head->data, \
							ft_strlen(((t_line *)head->data)->line));
			term_other(TERM_DOWN, 1);
		}
	}
}

void	cur_move_to_index(t_line *line, int index)
{
	t_pos		cur_pos;
	t_winsize	winsize;
	int			x;
	int			y;

	cur_pos = get_cur_pos();
	winsize = get_winsize();
	y = cur_pos.y + (((index + line->prompt->size - 1) / winsize.ws_col)\
			- ((line->index + line->prompt->size - 1) / winsize.ws_col)) - 1;
	if ((line->index + line->prompt->size) % winsize.ws_col == 0)
		--y;
	if ((index + line->prompt->size) % winsize.ws_col == 0)
		++y;
	if (y == winsize.ws_row)
	{
		--y;
		term_other(TERM_END, 1);
		term_other(TERM_SCROLL_UP, 1);
	}
	x = (index + line->prompt->size) % winsize.ws_col;
	line->index = index;
	cur_mov(x, y);
}
