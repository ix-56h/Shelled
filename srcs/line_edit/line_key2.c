/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:32:29 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/04 03:57:26 by akeiflin         ###   ########.fr       */
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

int		ctrl_d_act(t_line **line, t_dl_node **head, char mode)
{
	t_line	*tmp;

	if (mode & READ_MODE_LINE)
	{
		if (dl_find_data(*head, *line)->prev == NULL\
				&& (*line)->line[0] == '\0')
		{
			free_line(*line);
			*line = init_line(NULL, ft_strdup("exit")\
								, 4, new_prompt(PROMPT_DEFAULT));
			(*head)->data = *line;
			return (1);
		}
	}
	else if (mode & READ_MODE_HEREDOC)
	{
		tmp = init_line(NULL, ft_strdup("\004"), 0, NULL);
		dl_append(head, tmp);
		*line = tmp;
		return (1);
	}
	return (0);
}

int		ctrl_c_act(t_line **line, t_dl_node **head, char mode)
{
	if (mode & READ_MODE_LINE)
	{
		dl_free_with_data(*head, free_line);
		*head = NULL;
		*line = init_line(NULL, ft_strdup(""), 0, new_prompt(PROMPT_DEFAULT));
		dl_append(head, *line);
		(*head)->data = *line;
	}
	else if (mode & READ_MODE_HEREDOC)
	{
		(*line)->line[0] = '\030';
		(*line)->line[1] = '\0';
	}
	return (1);
}
