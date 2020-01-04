/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:35:42 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/04 19:13:41 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "libft.h"
#include "ligne.h"

struct termios	*save_term(int act)
{
	static struct termios	save;
	char					*term;

	term = getenv("TERM");
	if (act == 1)
	{
		if (term == NULL)
			return (NULL);
		if (tgetent(NULL, term) < 0)
			return (NULL);
		if (tcgetattr(STDIN_FILENO, &save) == -1)
			return (NULL);
	}
	return (&save);
}

int				restore_term(void)
{
	struct termios	*termios;

	if ((termios = save_term(0)) == NULL)
		return (-1);
	if (tcsetattr(STDIN_FILENO, 0, termios) == -1)
		return (-1);
	return (1);
}

int				set_term_mode(void)
{
	struct termios	*tmp;
	struct termios	termios;

	if ((tmp = save_term(1)) == NULL)
		return (-1);
	termios = *tmp;
	termios.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, 0, &termios) == -1)
		return (-4);
	return (1);
}

int				init_term(void)
{
	struct termios	*tmp;
	struct termios	termios;
	char			*buff;
	char			*term;

	term = getenv("TERM");
	if (!term || ft_strcmp(term, "xterm-256color") != 0)
		return (-1);
	if (!isatty(STDIN_FILENO))
		return (-1);
	return (set_term_mode());
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