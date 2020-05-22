/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:12:14 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 01:46:59 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ligne.h"

void			term_other(char *str, int iter)
{
	char *buff;

	buff = tgetstr(str, NULL);
	if (buff)
	{
		while (iter--)
			tputs(buff, 1, &ft_putchar);
	}
}

void			cur_mov(int y, int x)
{
	char *buff;

	buff = tgetstr("cm", NULL);
	tputs(tgoto(buff, y, x), 1, &ft_putchar);
}
