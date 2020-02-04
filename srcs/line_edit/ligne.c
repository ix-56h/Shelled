/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ligne.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 01:04:49 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/04 05:31:33 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "sh.h"
#include "libft.h"
#include "ligne.h"

void			init_and_read(t_line **line, t_dl_node **head, char mode\
							, t_prompt *prompt)
{
	*line = init_line(NULL, NULL, 0, prompt);
	if (mode & MODE_NO_NEWLINE)
		(*line)->no_newline = 1;
	ft_putstr((*line)->prompt->str);
	dl_append(head, *line);
	read_loop(line, head, mode);
	ft_putchar('\n');
}

char			*sub_run_heredoc(t_line **line, t_dl_node **head)
{
	t_dl_node		*tmp_node;
	char			*ret;

	tmp_node = dl_find_data(*head, *line);
	if (tmp_node && tmp_node->prev)
		tmp_node->prev->next = NULL;
	else
		*head = NULL;
	tmp_node->prev = NULL;
	dl_free_with_data(tmp_node, free_line);
	ret = concat_lines(*head, 1);
	if (ret)
		ret = ft_strljoin(ret, "\n", FIRST);
	dl_free_with_data(*head, free_line);
	signal(SIGINT, SIG_DFL);
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}

char			*run_heredoc(char *endstring)
{
	t_dl_node		*head;
	t_line			*line;

	signal(SIGINT, ctrl_c_line_handler);
	head = NULL;
	init_and_read(&line, &head, READ_MODE_LIMITED | READ_MODE_HEREDOC\
					, new_prompt(PROMPT_HEREDOC));
	if (heredoc_ctrl_c(head, line))
		return (NULL);
	while (ft_strcmp(line->line, endstring) != 0 \
						&& ft_strcmp(line->line, "\004") != 0)
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		init_and_read(&line, &head, READ_MODE_LIMITED | READ_MODE_HEREDOC\
				, new_prompt(PROMPT_HEREDOC));
		if (heredoc_ctrl_c(head, line))
			return (NULL);
	}
	move_cur_on_last_line(dl_find_data(head, line));
	return (sub_run_heredoc(&line, &head));
}

static void		is_finished_loop(t_line **line, t_dl_node **head)
{
	char	*tmp_ret;

	tmp_ret = concat_lines(*head, 0);
	while (!is_finished(tmp_ret))
	{
		if (dl_find_data(*head, *line)->next)
			move_cur_on_last_line(dl_find_data(*head, *line));
		init_and_read(line, head, READ_MODE_FULL | READ_MODE_LINE\
				| MODE_NO_NEWLINE, new_prompt("command>"));
		free(tmp_ret);
		tmp_ret = concat_lines(*head, 0);
	}
	if (tmp_ret)
		free(tmp_ret);
}

char			*run_line_edit(void)
{
	t_dl_node		*head;
	t_line			*line;
	char			*ret;

	signal(SIGINT, ctrl_c_line_handler);
	head = NULL;
	init_and_read(&line, &head, READ_MODE_FULL | READ_MODE_LINE\
					, new_prompt(PROMPT_DEFAULT));
	while (is_multiline(head))
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		init_and_read(&line, &head, READ_MODE_LIMITED | READ_MODE_LINE\
						, new_prompt(PROMPT_SUBLINE));
	}
	is_finished_loop(&line, &head);
	trim_and_add_historic(&head);
	move_cur_on_last_line(dl_find_data(head, line));
	historic_reset();
	ret = concat_lines(head, 1);
	head = NULL;
	signal(SIGINT, SIG_DFL);
	return ((ret) ? ret : ft_strdup(""));
}
