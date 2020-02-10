/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 00:27:35 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:15:54 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	xprecision_handler(char *buf, t_flags *f, t_counts *c, long long n)
{
	int		len;

	len = f->len;
	if (f->minus)
		f->d && n > 0 ? print_ox(buf, c, f->c) : 0;
	while (len < f->p)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = '0';
		len++;
	}
}

void	xwidthr_handler(long long n, char *buf, t_flags *f, t_counts *c)
{
	char	ch;
	int		len;

	len = f->len;
	ch = ' ';
	f->zero && f->p == -1 ? ch = '0' : 0;
	if (f->p > len)
		len = f->p;
	f->d && n > 0 ? len += 2 : 0;
	if (f->zero)
		f->d && n > 0 ? print_ox(buf, c, f->c) : 0;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ch;
		len++;
	}
	!f->zero && f->d && n > 0 ? print_ox(buf, c, f->c) : 0;
	xprecision_handler(buf, f, c, n);
}

void	xwidthl_handler(char *buf, t_flags *f, t_counts *c, long long n)
{
	int		len;

	len = f->len;
	if (f->p > len)
		len = f->p;
	f->d && n > 0 ? len += 2 : 0;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ' ';
		len++;
	}
}

void	shitty_x(char *buf, t_flags *f, t_counts *c, long long nbr)
{
	if ((f->m > f->len || f->p > f->len) && !f->minus)
		xwidthr_handler(nbr, buf, f, c);
	if ((f->m > f->len || f->p > f->len) && !f->minus)
	{
		if (!(f->p == 0 && nbr == 0))
			convert_hex(buf, c, nbr, f->c == 'x' ? 'a' : 'A');
	}
	else if ((f->m > f->len || f->p > f->len) && f->minus)
	{
		xprecision_handler(buf, f, c, nbr);
		if (!(f->p == 0 && nbr == 0))
			convert_hex(buf, c, nbr, f->c == 'x' ? 'a' : 'A');
		if (f->m > f->p && f->m > f->len)
			xwidthl_handler(buf, f, c, nbr);
	}
	else
	{
		f->d && nbr > 0 ? print_ox(buf, c, f->c) : 0;
		if (!(f->p == 0 && nbr == 0))
			convert_hex(buf, c, nbr, f->c == 'x' ? 'a' : 'A');
	}
}

void	handler_x(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	signed long long	nbr;

	if (f->length == L_L)
		nbr = (unsigned long)va_arg(ap, unsigned long);
	else if (f->length == L_LL)
		nbr = (unsigned long long)va_arg(ap, unsigned long long);
	else
		nbr = (unsigned int)va_arg(ap, unsigned int);
	f->len = (int)ft_nbrlen_base(nbr, 16) + 1;
	(f->p == 0 && nbr == 0) ? f->len = 0 : 0;
	shitty_x(buf, f, c, nbr);
}
