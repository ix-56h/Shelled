/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:20:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 00:57:34 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include "ligne.h"

void	ctrl_c_line_handler(int lel)
{
	(void)lel;
	ioctl(STDOUT_FILENO, TIOCSTI, "\030");
	add_set("?", "130");
}

int		heredoc_ctrl_c(t_dl_node *head, t_line *line)
{
	if (ft_strcmp(line->line, "\030") == 0)
	{
		dl_free_with_data(head, free_line);
		return (1);
	}
	return (0);
}
