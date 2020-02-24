/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controleur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:53:43 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/24 18:07:28 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ligne.h"

static int	break_read_loop(t_dl_node *head, t_line *line)
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

static int	test_term_size(void)
{
	t_winsize winsize;

	winsize = get_winsize();
	if (winsize.ws_col == 0 || winsize.ws_row == 0)
		return (0);
	return (1);
}

int			test_keys(char *buff, t_line **line, t_dl_node **head)
{
	if (ft_strcmp(buff, KEY_SUPR) == 0)
	{
		suppr_act(*line, head);
		return (1);
	}
	else if (ft_strcmp(buff, KEY_HOME) == 0)
	{
		cur_move_to_index(*line, 0);
		return (1);
	}
	else if (ft_strcmp(buff, KEY_END) == 0)
	{
		cur_move_to_index(*line, ft_strlen((*line)->line));
		return (1);
	}
	return (0);
}

static int	sub_read_loop(t_line **line, t_dl_node **head, char mode\
				, int readsize)
{
	char	buff[BUFFSIZE + 1];

	ft_bzero(buff, sizeof(char) * BUFFSIZE + 1);
	if ((readsize = read(STDIN_FILENO, buff, BUFFSIZE)) > -1 && ft_strlen(buff))
	{
		while (!test_term_size())
			;
		if (ft_isallprint(buff) && term_can_print(*head, readsize))
			write_on_line(*line, readsize, buff, head);
		else if (ft_strcmp(buff, "\n") == 0 && break_read_loop(*head, *line))
			return (0);
		else if (test_keys(buff, line, head))
			(void)0;
		else if (ft_strcmp(buff, "\030") == 0 && ctrl_c_act(line, head, mode))
			return (0);
		else if (ft_strcmp(buff, "\004") == 0 && ctrl_d_act(line, head, mode))
			return (0);
		else
			arrow_line_action(line, buff, head, mode);
	}
	return (1);
}

int			read_loop(t_line **line, t_dl_node **head, char mode)
{
	int		readsize;

	readsize = 0;
	while (!!!!!!!!!!!!!!!!!!!!!!!0)
	{
		if (!sub_read_loop(line, head, mode, readsize))
			break ;
	}
	return (0);
}
