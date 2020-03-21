/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controleur2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:03:11 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 05:03:29 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ligne.h"

void		arrow_line_action(t_line **line, char *buff, t_dl_node **head,
								char mode)
{
	if (ft_strcmp(buff, KEY_LEFT_CODE) == 0)
		arrow_left_act(*line);
	else if (ft_strcmp(buff, KEY_RIGHT_CODE) == 0)
		arrow_right_act(*line);
	else if (ft_strcmp(buff, KEY_UP_CODE) == 0 && mode & READ_MODE_FULL)
		arrow_up_act(line, head);
	else if (ft_strcmp(buff, KEY_DOWN_CODE) == 0 && mode & READ_MODE_FULL)
		arrow_down_act(line, head);
	else if (is_ctrl_left(buff))
		cur_move_to_index(*line, get_last_word_index(*line));
	else if (is_ctrl_right(buff))
		cur_move_to_index(*line, get_next_word_index(*line));
	else if (is_ctrl_up(buff) && mode & READ_MODE_LIMITED \
			&& dl_find_data(*head, *line)->prev)
		arrow_ctrl_up(line, head);
	else if (is_ctrl_down(buff) && mode & READ_MODE_LIMITED \
			&& dl_find_data(*head, *line)->next)
		arrow_ctrl_down(line, head);
}
