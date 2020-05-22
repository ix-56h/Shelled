/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_key1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:15:18 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 01:43:23 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ligne.h"

void	arrow_up_act(t_line **line, t_dl_node **head)
{
	t_dl_node		*historic;

	if ((historic = historic_get_next()))
	{
		clear_node_line(*head);
		dl_free_with_data(*head, *free_line);
		*head = dup_line_node(historic);
		print_historique(historic);
		*line = dl_get_last(*head)->data;
		move_cur_on_newline(*line);
	}
}

void	arrow_down_act(t_line **line, t_dl_node **head)
{
	t_dl_node	*historic;

	if (historic_on_use(0))
	{
		clear_node_line(*head);
		if ((historic = historic_get_last()))
		{
			dl_free_with_data(*head, *free_line);
			*head = dup_line_node(historic);
			print_historique(historic);
			*line = dl_get_last(*head)->data;
			move_cur_on_newline(*line);
		}
		else
		{
			dl_free_with_data(*head, *free_line);
			*head = NULL;
			dl_push(head, init_line(NULL, NULL, 0, new_prompt(PROMPT_DEFAULT)));
			print_historique(*head);
			*line = dl_get_last(*head)->data;
			move_cur_on_newline(*line);
		}
	}
}

void	arrow_left_act(t_line *line)
{
	t_pos	pos;

	if (line->index > 0)
	{
		pos = get_cur_pos();
		if (pos.x == 1 && pos.y == 1)
			term_other(TERM_SCROLL_DOWN, 1);
		if (pos.x == 1)
			cur_mov(get_winsize().ws_col - 1, get_cur_pos().y - 2);
		else
			term_other(TERM_LEFT, 1);
		--line->index;
	}
}

void	arrow_right_act(t_line *line)
{
	t_pos	pos;

	if ((size_t)line->index < ft_strlen(line->line))
	{
		pos = get_cur_pos();
		if (pos.y == get_winsize().ws_col + 1)
			term_other(TERM_SCROLL_UP, 1);
		if (pos.x == get_winsize().ws_col)
			cur_mov(0, get_cur_pos().y);
		else
			term_other(TERM_RIGHT, 1);
		++line->index;
	}
}
