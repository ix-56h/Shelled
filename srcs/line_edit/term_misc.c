/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:35:42 by akeiflin          #+#    #+#             */
/*   Updated: 2019/12/05 16:53:00 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "libft.h"
#include "ligne.h"

int				init_term(void)
{
	struct termios	*s_termios;
	char			*buff;
	char			*term;

	term = getenv("TERM");
	if (!term || ft_strcmp(term, "xterm-256color") != 0)
		return (-22);
	if (!isatty(STDIN_FILENO))
		return (-20);
	s_termios = save_term();
	if (s_termios == NULL)
		return (-21);
	s_termios->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, 0, s_termios) == -1)
		return (-4);
	return (1);
}

struct termios	*save_term(void)
{
	static int				i = 0;
	static struct termios	save;
	char					*term;

	if (i == 0)
	{
		term = getenv("TERM");
		if (term == NULL)
			return (NULL);
		if (tgetent(NULL, term) < 0)
			return (NULL);
		if (tcgetattr(STDIN_FILENO, &save) == -1)
			return (NULL);
		++i;
	}
	return (&save);
}

void	term_other(char *str, int iter)
{
	char *buff;

	buff = tgetstr(str, NULL);
	if (buff)
	{
		while (iter--)
			tputs(buff, 1, &ft_putchar);
	}
}

void	cur_mov(int y, int x)
{
	char *buff;

	buff = tgetstr("cm", NULL);
	tputs(tgoto(buff, y, x), 1, &ft_putchar);
}