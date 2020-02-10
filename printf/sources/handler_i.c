/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 00:38:32 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/22 17:15:52 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		process_handler(char *buf, t_flags *f, t_counts *c, long long n)
{
	int	max;

	max = f->len;
	n < 0 && ((!f->zero || f->minus) || (f->zero && f->m <= max + 1))
		? write_in_buff(buf, '-', c) : 0;
	n < 0 ? max-- : 0;
	if (n >= 0 && f->s && (f->minus || f->m <= max) && !f->plus)
		write_in_buff(buf, ' ', c);
	f->plus && n >= 0 && (!f->zero || f->p != -1 || f->m <= max || f->minus)
		? write_in_buff(buf, '+', c) : 0;
	if (n == 0 && f->p == 0)
		return ;
	if (f->p > max)
	{
		while (f->p > max++)
			write_in_buff(buf, '0', c);
	}
	write_nbr(buf, c, n);
}

void		width_handler(char *buf, t_flags *f, t_counts *c, long long n)
{
	char	ch;
	int		max;

	ch = ' ';
	max = (f->p > f->len ? f->p : f->len);
	(n >= 0 && f->plus) ? max++ : 0;
	(n >= 0 && f->s && !f->plus) ? max++ : 0;
	(n < 0 && f->p >= f->len) ? max++ : 0;
	(n == 0 && f->p == 0) ? max-- : 0;
	if (f->m > max)
	{
		if (n >= 0 && f->s && !f->minus && !f->plus)
			write_in_buff(buf, ' ', c);
		!f->minus && f->zero && f->p == -1 ? ch = '0' : 0;
		n < 0 && f->zero && f->p == -1 && !f->minus ? write_in_buff(buf, '-', c)
			: 0;
		f->plus && n >= 0 && (f->zero && !f->minus)
			&& f->p == -1 ? write_in_buff(buf, '+', c)
			: 0;
		while (f->m > max++)
			write_in_buff(buf, ch, c);
	}
}

void		handler_i(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	long long	n;

	n = convert_int_arg(ap, *f);
	f->len = ft_size_digit(n);
	f->m >= f->len && !f->minus ? width_handler(buf, f, c, n) : 0;
	process_handler(buf, f, c, n);
	f->m >= f->len && f->minus ? width_handler(buf, f, c, n) : 0;
}
