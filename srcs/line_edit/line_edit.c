/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:08:20 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/16 15:47:48 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ligne.h"

void			ft_insert_in_line(char *line, char *buff, int index)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char) * (ft_strlen(line) - index + 1));
	ft_strcpy(tmp, &line[index]);
	ft_strcpy(&line[index], buff);
	ft_strcpy(&line[index + ft_strlen(buff)], tmp);
	free(tmp);
}

static void		expend_line_alloc(t_line *line, int readsize)
{
	char		*new_str;
	size_t		new_size;

	if (readsize > BUFFSIZE)
		new_size = line->allocsize + readsize;
	else
		new_size = line->allocsize + BUFFSIZE;
	new_str = ft_calloc(sizeof(char) * (new_size + 1));
	ft_strcpy(new_str, line->line);
	free(line->line);
	line->line = new_str;
	line->allocsize = new_size;
}

static int		iterm_fix(t_line *line)
{
	if (get_env(g_env, "LC_TERMINAL") &&
			ft_strcmp(get_env(g_env, "LC_TERMINAL"), "iTerm2") == 0)
	{
		if ((ft_strlen(line->line) + line->prompt->size)\
				% get_winsize().ws_col == 0)
		{
			term_other(TERM_UP, 1);
			cur_move_to_index(line, line->index);
			return (1);
		}
	}
	return (0);
}

void			write_on_line(t_line *line, int readsize\
							, char *buff, t_dl_node **head)
{
	t_dl_node	*tmp;

	if (ft_strlen(line->line) + readsize > line->allocsize)
		expend_line_alloc(line, readsize);
	ft_insert_in_line(line->line, buff, line->index);
	line->index += readsize;
	ft_putstr(buff);
	move_cur_on_newline(line);
	if (line->line[line->index])
	{
		term_other(TERM_SAVE_CUR, 1);
		ft_putstr(&line->line[line->index]);
		if ((ft_strlen(line->line) + line->prompt->size)\
				% get_winsize().ws_col == 0)
			ft_putchar('\n');
		term_other(TERM_CLEAR_CUR_END, 1);
		if ((tmp = dl_find_data(*head, line)) && tmp->next)
		{
			ft_putchar('\n');
			print_historique(tmp->next);
		}
		term_other(TERM_CLEAR_CUR_END, 1);
		if (!iterm_fix(line))
			term_other(TERM_LOAD_CUR, 1);
	}
}

void			print_historique(t_dl_node *historic)
{
	t_line	*tmp_line;

	while (historic)
	{
		tmp_line = historic->data;
		ft_putstr(tmp_line->prompt->str);
		ft_putstr(tmp_line->line);
		if ((ft_strlen(tmp_line->line) + tmp_line->prompt->size)\
				% get_winsize().ws_col == 0)
			ft_putchar('\n');
		if (historic->next)
			ft_putchar('\n');
		historic = historic->next;
	}
}
