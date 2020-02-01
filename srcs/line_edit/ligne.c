#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "sh.h"
#include "libft.h"
#include "ligne.h"

static void	ctrl_c_handler(int lel)
{
	(void)lel;
	ioctl(STDOUT_FILENO, TIOCSTI, "\030");
}

int		heredoc_ctrl_c(t_dl_node *head, t_line *line)
{
	if (ft_strcmp(line->line, "\030") == 0)
	{
		dl_free_whith_content(head, free_line);
		return (1);
	}
	return (0);
}

void	heredoc_set_line_and_run(t_dl_node **head, t_line **line)
{
	*line = init_line(NULL, NULL, 0, new_prompt(PROMPT_HEREDOC));
	ft_putstr((*line)->prompt->str);
	dl_append(head, *line);
	read_loop(line, head, READ_MODE_LIMITED | READ_MODE_HEREDOC);
}

char	*run_heredoc(char	*endstring)
{
	t_dl_node		*head;
	t_line			*line;
	char			*ret;
	t_dl_node		*tmp_node; 
	
	signal(SIGINT, ctrl_c_handler);
	head = NULL;
	heredoc_set_line_and_run(&head, &line);
	if (heredoc_ctrl_c(head, line))
		return (NULL);
	while (ft_strcmp(line->line, endstring) != 0 && ft_strcmp(line->line, "\004") != 0)
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		heredoc_set_line_and_run(&head, &line);
		if (heredoc_ctrl_c(head, line))
			return (NULL);
	}
	move_cur_on_last_line(dl_find_data(head, line));
	tmp_node = dl_find_data(head, line);
	if (tmp_node && tmp_node->prev)
		tmp_node->prev->next = NULL;
	else
		head = NULL;
	tmp_node->prev = NULL;
	dl_free_whith_content(tmp_node, free_line);
	ret = concat_lines(head, 1);
	if (ret)
		ret = ft_strljoin(ret, "\n", FIRST);
	dl_free_whith_content(head, free_line);
	signal(SIGINT, SIG_DFL);
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}

int		is_finished(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if(line[i] == ' ')
			i--;
		else
		{
			if (line[i] == '|')
			{
				if (i - 1 >= 0 && line[i - 1] == '|')
					return (0);
			}
			else if (line[i] == '&')
			{
				if (i - 1 >= 0 && line[i - 1] == '&')
					return (0);
			}
			else
				return (1);
		}
		
		--i;
	}
	return (1);
}

char	*run_line_edit(void)
{
	t_dl_node		*head;
	t_line			*line;
	char			*ret;
	char			*tmp_ret;

	signal(SIGINT, ctrl_c_handler);
	head = NULL;
	line = init_line(NULL, NULL, 0, new_prompt(PROMPT_DEFAULT));
	ft_putstr(line->prompt->str);
	dl_append(&head, line);
	read_loop(&line, &head, READ_MODE_FULL | READ_MODE_LINE);
	while (is_multiline(head))
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		line = init_line(NULL, NULL, 0, new_prompt(PROMPT_SUBLINE));
		ft_putstr(line->prompt->str);
		dl_append(&head, line);
		read_loop(&line, &head, READ_MODE_LIMITED | READ_MODE_LINE);
	}
	tmp_ret = concat_lines(head, 0);
	while (!is_finished(tmp_ret))
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		line = init_line(NULL, NULL, 0, new_prompt("command>"));
		line->no_newline = 1;
		ft_putstr(line->prompt->str);
		dl_append(&head, line);
		read_loop(&line, &head, READ_MODE_LIMITED | READ_MODE_LINE);
		free(tmp_ret);
		tmp_ret = concat_lines(head, 0);
	}
	if (tmp_ret)
		free(tmp_ret);
	add_historic(head);
	move_cur_on_last_line(dl_find_data(head, line));
	historic_reset();
	ret = concat_lines(head, 1);
	head = NULL;
	signal(SIGINT, SIG_DFL);
	return (ret);
}
