/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:45:15 by niguinti          #+#    #+#             */
/*   Updated: 2019/03/24 12:34:09 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		process_handlerf(char *buf, t_flags *f, t_counts *c, long double n)
{
	int	max;

	max = f->len;
	n < -0 && (f->minus || !f->zero || f->p > -1) ? write_in_buff(buf, '-', c)
		: 0;
	n < -0 ? max-- : 0;
	if (n >= 0 && f->s && !f->plus && (!f->zero || f->minus))
		write_in_buff(buf, ' ', c);
	f->plus && n >= 0 && (!f->zero || f->p != -1) ? write_in_buff(buf, '+', c)
		: 0;
	if (n == 0 && f->p == 0)
		return ;
	if (f->p > max)
	{
		while (f->p > max++)
			write_in_buff(buf, '0', c);
	}
	write_nbr(buf, c, (int)n);
	f->p > 0 || f->d ? write_in_buff(buf, '.', c) : 0;
	write_float(buf, c, n, f->p);
}

void		width_handlerf(char *buf, t_flags *f, t_counts *c, long double n)
{
	char	ch;
	int		max;

	ch = ' ';
	max = (f->p > f->len ? f->p : f->len);
	(n >= 0 && f->plus) ? max++ : 0;
	(n >= 0 && f->s && !f->plus) ? max++ : 0;
	(n < 0 && f->p >= f->len) ? max++ : 0;
	if (n >= 0 && f->s && !f->minus && !f->plus && f->p == -1)
		write_in_buff(buf, ' ', c);
	(n == 0 && f->p == 0) ? max-- : 0;
	if (f->m > max)
	{
		!f->minus && f->zero && f->p == -1 ? ch = '0' : 0;
		n < 0 && f->zero && f->p == -1 && !f->minus ? write_in_buff(buf, '-', c)
			: 0;
		f->plus && n >= 0 && f->p == -1 ? write_in_buff(buf, '+', c) : 0;
		while (f->m > max++)
			write_in_buff(buf, ch, c);
	}
}

long double	convert_float_arg(va_list ap, t_flags f)
{
	long double	ret;

	if (f.length == L_LLL)
		ret = va_arg(ap, long double);
	else if (f.length == L_L)
		ret = va_arg(ap, double);
	else
		ret = (float)va_arg(ap, double);
	return (ret);
}

int			ft_size_float(long double n, int p)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		n *= -1;
		ret = 1;
	}
	ret += ft_size_digit(n);
	n -= (int)n;
	p > 0 ? ret++ : 0;
	while (p--)
	{
		n *= 10;
		n -= (int)n;
		ret++;
	}
	return (ret);
}

void		handler_f(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	long double	n;

	f->p == -1 ? f->p = 6 : 0;
	n = convert_float_arg(ap, *f);
	f->len = ft_size_float(n, f->p);
	f->m >= f->len && !f->minus ? width_handlerf(buf, f, c, n) : 0;
	process_handlerf(buf, f, c, n);
	f->m > f->len && f->minus ? width_handlerf(buf, f, c, n) : 0;
}
