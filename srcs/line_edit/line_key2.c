/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:32:29 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/07 18:27:03 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ligne.h"

void	arrow_ctrl_down(t_line **line, t_dl_node **head)
{
	t_dl_node	*current;

	current = dl_find_data(*head, *line);
	if (current)
	{
		cur_move_to_index(*line, ft_strlen((*line)->line));
		term_other(TERM_DOWN, 1);
		*line = current->next->data;
//		g_for_resize.line = *line;
		cur_move_to_index(*line, 0);
		(*line)->index = 0;
	}
}

void	arrow_ctrl_up(t_line **line, t_dl_node **head)
{
	t_dl_node	*current;

	current = dl_find_data(*head, *line);
	if (current)
	{
		cur_move_to_index(*line, 0);
		term_other(TERM_UP, 1);
		*line = current->prev->data;
//		g_for_resize.line = *line;
		cur_move_to_index(*line, 0);
		(*line)->index = 0;
	}
}

void	suppr_act(t_line *line, t_dl_node **head)
{
	t_dl_node	*tmp;

	if (line->index > 0)
	{
		ft_strcpy(&line->line[line->index - 1], &line->line[line->index]);
		cur_move_to_index(line, line->index - 1);
		term_other(TERM_SAVE_CUR, 1);
		ft_putstr(&line->line[line->index]);
		term_other(TERM_CLEAR_CUR_END, 1);
		if ((tmp = dl_find_data(*head, line)) && tmp->next)
		{
			ft_putchar('\n');
			print_historique(tmp->next);
		}
		term_other(TERM_CLEAR_CUR_END, 1);
		term_other(TERM_LOAD_CUR, 1);
	}
}