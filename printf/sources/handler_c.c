/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:04:32 by niguinti          #+#    #+#             */
/*   Updated: 2019/03/24 12:34:00 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		write_c(char *buf, t_counts *c, char ch)
{
	c->b == c->bs ? flush_buff(buf, c) : 0;
	buf[c->b++] = ch;
}

void		widthc_handler(char *buf, t_flags *f, t_counts *c)
{
	int		len;
	char	ch;

	ch = ' ';
	len = 1;
	f->zero && f->m > 1 ? ch = '0' : 0;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ch;
		len++;
	}
}

void		handler_c(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	char	ch;

	ch = va_arg(ap, unsigned int);
	if (f->m > 1 && !f->minus)
		widthc_handler(buf, f, c);
	if (f->m > 1 && !f->minus)
		write_c(buf, c, ch);
	else if (f->m > 1 && f->minus)
	{
		write_c(buf, c, ch);
		widthc_handler(buf, f, c);
	}
	else
		write_c(buf, c, ch);
}
