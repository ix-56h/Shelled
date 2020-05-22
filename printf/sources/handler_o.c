/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 05:52:28 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 03:54:47 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_octal(char *buf, t_counts *c, unsigned long long n)
{
	char				s[23];
	int					len;
	long long unsigned	n2;

	n2 = n;
	len = 0;
	ft_bzero(s, 23);
	while (n2 != 0)
	{
		n2 = n2 / 8;
		len++;
	}
	n == 0 ? len = 1 : 0;
	while (len--)
	{
		s[len] = (n % 8 < 10) ? n % 8 + '0' : n % 8 - 10;
		n /= 8;
	}
	write_str(buf, c, s);
}

void	oprecision_handler(char *buf, t_flags *f, t_counts *c)
{
	int	len;

	len = f->len;
	while (len < f->p)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = '0';
		len++;
	}
}

void	owidthr_handler(char *buf, t_flags *f, t_counts *c)
{
	char	ch;
	int		len;

	len = f->len;
	ch = ' ';
	f->zero && f->p == -1 ? ch = '0' : 0;
	f->p > f->len ? len = f->p : 0;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ch;
		len++;
	}
	if (f->len < f->p)
		oprecision_handler(buf, f, c);
}

void	owidthl_handler(char *bu, t_flags *f, t_counts *c)
{
	if (f->p > f->len)
		f->len = f->p;
	while (f->len < f->m)
	{
		c->b == c->bs ? flush_buff(bu, c) : 0;
		bu[c->b++] = ' ';
		f->len++;
	}
}

void	handler_o(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	unsigned long long	nbr;
	unsigned long long	n2;

	nbr = convert_u_arg(ap, *f);
	shitty_o(f, &n2, &nbr);
	if ((f->m > f->len || f->p > f->len) && !f->minus)
		owidthr_handler(buf, f, c);
	if ((f->m > f->len || f->p > f->len) && !f->minus)
	{
		f->d && f->p <= f->len && nbr > 0 ? write_in_buff(buf, '0', c) : 0;
		(f->p == 0 && nbr == 0 && !f->d) ? 0 : convert_octal(buf, c, nbr);
		return ;
	}
	else if ((f->m > f->len || f->p > f->len) && f->minus)
	{
		f->d && f->p <= f->len && nbr > 0 ? write_in_buff(buf, '0', c) : 0;
		oprecision_handler(buf, f, c);
		(f->p == 0 && nbr == 0 && !f->d) ? 0 : convert_octal(buf, c, nbr);
		if (f->m > f->p && f->m > f->len)
			owidthl_handler(buf, f, c);
		return ;
	}
	f->d && f->p <= f->len && nbr > 0 ? write_in_buff(buf, '0', c) : 0;
	(f->p == 0 && nbr == 0 && !f->d) ? 0 : convert_octal(buf, c, nbr);
}
