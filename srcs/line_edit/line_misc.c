/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:22:13 by akeiflin          #+#    #+#             */
/*   Updated: 2019/12/31 00:47:06 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"
#include "ligne.h"

char	*concat_lines(t_dl_node *head)
{
	char	*str;

	str = NULL;
	if (!head->next)
		return (ft_strdup(((t_line *)head->data)->line));
	while (head->next)
	{
		str = ft_strljoin(str, ((t_line *)head->data)->line, FIRST);	
		str = ft_strljoin(str, "\n", FIRST);
		head = head->next;
	}
	str = ft_strljoin(str, ((t_line *)head->data)->line, FIRST);
	return (str);
}

int		count_row_in_line(t_line *line, t_winsize winsize)
{
	int		len;
	int		res;

	res = 0;
	len = ft_strlen(line->line);
	res += (len + line->prompt->size) / winsize.ws_col + 1;
	if ((len + line->prompt->size) % winsize.ws_col == 0)
		++res;
	return (res);
}

int		term_can_print(t_dl_node *head, int readsize)
{
	t_line		*tmp;
	int			res;
	t_winsize	winsize;

	winsize = get_winsize();
	res = 0;
	while (head->next)
	{
		tmp = head->data;
		count_row_in_line(tmp, winsize);
		head = head->next;
	}
	tmp = head->data;
	res += (ft_strlen(tmp->line) + tmp->prompt->size + readsize) / winsize.ws_col + 1;
	if ((ft_strlen(tmp->line) + tmp->prompt->size) % winsize.ws_col == 0)
		--res;
	if (res <= winsize.ws_row)
		return (1);
	else
		return (0);
}

void	handle_resize(int signo)
{
	t_dl_node	*last;
	t_dl_node	*head;
	t_line	*line;

	signal(SIGWINCH, SIG_DFL);
	head = g_for_resize.node;
	line = g_for_resize.line;
	term_other("ho", 1);
	term_other(TERM_CLEAR_CUR_END, 1);
	last = dl_get_last(head);
	print_historique(head);
	while (last && last->data != line)
	{
		cur_move_to_index(last->data, 0);
		term_other(TERM_UP, 1);
		last = last->prev;
	}
	cur_move_to_index(last->data, ((t_line *)last->data)->index);
	signal(SIGWINCH, &handle_resize);
}