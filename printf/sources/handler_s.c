/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:13:20 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/18 21:42:15 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		write_s(char *buf, t_counts *c, char *s, int p)
{
	int		i;

	i = 0;
	if (p != -1)
	{
		while (s[i] && p != 0)
		{
			c->b == c->bs ? flush_buff(buf, c) : 0;
			buf[c->b++] = s[i++];
			p--;
		}
	}
	else
	{
		while (s[i])
		{
			c->b == c->bs ? flush_buff(buf, c) : 0;
			buf[c->b++] = s[i++];
		}
	}
}

void		widths_handler(char *s, char *buf, t_flags *f, t_counts *c)
{
	int		len;
	char	ch;

	ch = ' ';
	len = (int)ft_strlen(s);
	f->p > -1 && f->p < len ? len = f->p : 0;
	f->p > -1 && f->m > f->p && len > f->p ? f->m += f->p : 0;
	f->zero && f->m > len && !f->minus ? ch = '0' : 0;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ch;
		len++;
	}
}

void		handler_s(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	len = (int)ft_strlen(s);
	if ((f->m > len || f->m > f->p) && !f->minus)
		widths_handler(s, buf, f, c);
	if ((f->m > len || f->m > f->p) && !f->minus)
		write_s(buf, c, s, f->p);
	else if ((f->m > len || f->m > f->p) && f->minus)
	{
		write_s(buf, c, s, f->p);
		widths_handler(s, buf, f, c);
	}
	else
		write_s(buf, c, s, f->p);
}
