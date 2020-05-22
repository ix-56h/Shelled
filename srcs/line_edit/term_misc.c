/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:35:42 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/25 17:03:49 by ezonda           ###   ########.fr       */
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

struct termios	*save_initialised_term(int act)
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

int				restore_term(int act)
{
	struct termios	*termios;

	if (act == 1)
		if ((termios = save_term(0)) == NULL)
			return (-1);
	if (act == 2)
		if ((termios = save_initialised_term(0)) == NULL)
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
	save_initialised_term(1);
	return (1);
}

int				init_term(void)
{
	char			*term;

	term = getenv("TERM");
	if (!term || ft_strcmp(term, "xterm-256color") != 0)
	{
		ft_putstr("The terminal must be xterm-256color\n");
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr("Only interactive mode allowed\n");
		exit(1);
	}
	return (set_term_mode());
}
