/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 00:38:32 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:15:39 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		puh(char *buf, t_flags *f, t_counts *c, unsigned long long n)
{
	int	max;

	max = f->len;
	if (n == 0 && f->p == 0)
		return ;
	if (f->p > max)
	{
		while (f->p > max++)
			write_in_buff(buf, '0', c);
	}
	write_unsigned(buf, c, n);
}

void		wuh(char *buf, t_flags *f, t_counts *c, unsigned long long n)
{
	char	ch;
	int		max;

	ch = ' ';
	max = (f->p > f->len ? f->p : f->len);
	f->plus ? max++ : 0;
	(f->s && !f->plus) ? max++ : 0;
	if (f->s && !f->minus && !f->plus && f->p == -1)
		write_in_buff(buf, ' ', c);
	(n == 0 && f->p == 0) ? max-- : 0;
	if (f->m > max)
	{
		!f->minus && f->zero && f->p == -1 ? ch = '0' : 0;
		while (f->m > max++)
			write_in_buff(buf, ch, c);
	}
}

void		handler_u(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	unsigned long long	n;
	unsigned long long	n2;

	n = convert_u_arg(ap, *f);
	n2 = n;
	f->len = 0;
	while (++f->len && n2 != 0)
		n2 = n2 / 10;
	n > 0 ? f->len-- : 0;
	f->m >= f->len && !f->minus ? wuh(buf, f, c, n) : 0;
	puh(buf, f, c, n);
	f->m > f->len && f->minus ? wuh(buf, f, c, n) : 0;
}
