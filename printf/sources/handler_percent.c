/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 01:51:52 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/26 02:02:04 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handler_percent(char *buf, t_flags *f, t_counts *c)
{
	int		i;
	char	ch;

	i = 1;
	ch = (f->zero && !f->minus ? '0' : ' ');
	if (!f->minus)
	{
		while (f->m > i++)
			write_in_buff(buf, ch, c);
	}
	write_in_buff(buf, '%', c);
	if (f->minus)
	{
		while (f->m > i++)
			write_in_buff(buf, ch, c);
	}
}
