#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sh.h>
#include "libft.h"
#include "ligne.h"

char	*run_heredoc(char	*endstring)
{
	t_dl_node		*head;
	t_line			*line;
	char			*ret;
	t_dl_node		*tmp_node; 
	head = NULL;
	line = init_line(NULL, NULL, 0, new_prompt(PROMPT_HEREDOC));
	ft_putstr(line->prompt->str);
	dl_append(&head, line);
	read_loop(&line, &head, READ_MODE_LIMITED);
	while (ft_strcmp(line->line, endstring) != 0)
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		line = init_line(NULL, NULL, 0, new_prompt(PROMPT_HEREDOC));
		ft_putstr(line->prompt->str);
		dl_append(&head, line);
		read_loop(&line, &head, READ_MODE_LIMITED);
	}
	move_cur_on_last_line(dl_find_data(head, line));
	tmp_node = dl_find_data(head, line);
	if (tmp_node->prev)
		tmp_node->prev->next = NULL;
	else
		head = NULL;
	tmp_node->prev = NULL;
	dl_free_whith_content(tmp_node, free_line);
	ret = concat_lines(head);
	if (ret)
		ret = ft_strljoin(ret, "\n", FIRST);
	dl_free_whith_content(head, free_line);
	return (ret);
}

void	ctrl_c_handler(int lel)
{
	ioctl(STDOUT_FILENO, TIOCSTI, "\030");
}

char	*run_line_edit(void)
{
	t_dl_node		*head;
	t_line			*line;
	char			*ret;

	signal(SIGINT, ctrl_c_handler);
	head = NULL;
	line = init_line(NULL, NULL, 0, new_prompt(PROMPT_DEFAULT));
	ft_putstr(line->prompt->str);
	dl_append(&head, line);
	//g_for_resize.node = head;
	//g_for_resize.line = line;
	read_loop(&line, &head, READ_MODE_FULL);
	while (is_multiline(head))
	{
		if (dl_find_data(head, line)->next)
			move_cur_on_last_line(dl_find_data(head, line));
		line = init_line(NULL, NULL, 0, new_prompt(PROMPT_SUBLINE));
		ft_putstr(line->prompt->str);
		dl_append(&head, line);
		//g_for_resize.node = head;
		//g_for_resize.line = line;
		read_loop(&line, &head, READ_MODE_LIMITED);
	}
	add_historic(head);
	move_cur_on_last_line(dl_find_data(head, line));
	historic_reset();
	ret = concat_lines(head);
	head = NULL;
	signal(SIGINT, SIG_DFL);
	return (ret);
}
