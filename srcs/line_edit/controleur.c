/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controleur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:53:43 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/16 05:38:02 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ligne.h"

static int		break_read_loop(t_dl_node *head, t_line *line)
{
	if (is_multiline(head))
	{
		if (term_can_print(head, get_winsize().ws_col))
		{
			cur_move_to_index(line, ft_strlen(line->line));
			return (1);
		}
	}
	else
	{
		cur_move_to_index(line, ft_strlen(line->line));
		return (1);
	}
	return (0);
}


static int		test_term_size(void)
{
	t_winsize winsize;

	winsize = get_winsize();
	if (winsize.ws_col == 0 || winsize.ws_row == 0)
		return (0);
	return (1);
}

int				read_loop(t_line **line, t_dl_node **head, char mode)
{
	char	buff[BUFFSIZE + 1];
	int		readsize;

	while (!!!!!!!!!!!!!!!!!!!!!!!0)
	{
		ft_bzero(buff, sizeof(char) * BUFFSIZE + 1);
		if ((readsize = read(STDIN_FILENO, buff, BUFFSIZE)) > -1)
		{
			while (!test_term_size());
			if (ft_isallprint(buff) && term_can_print(*head, readsize))
				write_on_line(*line, readsize, buff, head);
			else if (ft_strcmp(buff, "\n") == 0 && break_read_loop(*head, *line))
				break ;
			else if (ft_strcmp(buff, KEY_SUPR) == 0)
				suppr_act(*line, head);
			else if (ft_strcmp(buff, KEY_HOME) == 0)
				cur_move_to_index(*line, 0);
			else if (ft_strcmp(buff, KEY_END) == 0)
				cur_move_to_index(*line, ft_strlen((*line)->line));
			else if (ft_strcmp(buff, "\030") == 0)
			{
				dl_free_whith_content(*head, free_line);
				*head = NULL;
				*line = init_line(NULL, ft_strdup(""), 0, new_prompt(PROMPT_DEFAULT));
				dl_append(head, *line);
				(*head)->data = *line;
				break ;

			}
			else
				arrow_line_action(line, buff, head, mode);
		}
	}
	ft_putchar('\n');
	return (0);
}

void	    	arrow_line_action(t_line **line, char *buff, t_dl_node **head, char mode)
{
	if (ft_strcmp(buff, KEY_LEFT_CODE) == 0)
		arrow_left_act(*line);
	else if (ft_strcmp(buff, KEY_RIGHT_CODE) == 0)
		arrow_right_act(*line);
	else if (ft_strcmp(buff, KEY_UP_CODE) == 0 && mode == READ_MODE_FULL)
		arrow_up_act(line, head);
	else if (ft_strcmp(buff, KEY_DOWN_CODE) == 0 && mode == READ_MODE_FULL)
		arrow_down_act(line, head);
	else if (ft_strcmp(buff, KEY_CTRL_LEFT_CODE) == 0)
		cur_move_to_index(*line, get_last_word_index(*line));
	else if (ft_strcmp(buff, KEY_CTRL_RIGHT_CODE) == 0)
		cur_move_to_index(*line, get_next_word_index(*line));
	else if (ft_strcmp(buff, KEY_CTRL_UP_CODE) == 0 && mode == READ_MODE_LIMITED && dl_find_data(*head, *line)->prev)
		arrow_ctrl_up(line, head);
	else if (ft_strcmp(buff, KEY_CTRL_DOWN_CODE) == 0 && mode == READ_MODE_LIMITED && dl_find_data(*head, *line)->next)
		arrow_ctrl_down(line, head);
}