#include <stdlib.h>
#include <sh.h>
#include "libft.h"
#include "ligne.h"


void	run_line_edit(t_sh *sh)
{
	t_dl_node		*head;
	t_line			*line;

	head = NULL;
	while (1)
	{
		line = init_line(NULL, NULL, 0, new_prompt(PROMPT_DEFAULT));
		ft_putstr(line->prompt->str);
		dl_append(&head, line);
		g_for_resize.node = head;
		g_for_resize.line = line;
		read_loop(&line, &head, READ_MODE_FULL);
		while (is_multiline(head))
		{
			if (dl_find_data(head, line)->next)
				move_cur_on_last_line(dl_find_data(head, line));
			line = init_line(NULL, NULL, 0, new_prompt(PROMPT_SUBLINE));
			ft_putstr(line->prompt->str);
			dl_append(&head, line);
			g_for_resize.node = head;
			g_for_resize.line = line;
			read_loop(&line, &head, READ_MODE_LIMITED);
		}
		add_historic(head);
		historic_reset();
		//concat_lines(head); Renvoie la string final
		head = NULL;
		if (ft_strcmp(line->line, "exit") == 0) //stop temporaire???
			break;
	}
	free_historic();
}