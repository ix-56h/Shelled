/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:10:04 by niguinti          #+#    #+#             */
/*   Updated: 2019/03/24 12:34:31 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pprecision_handler(long long n, char *buf, t_flags *f, t_counts *c)
{
	int		len;

	len = (int)ft_nbrlen_base(n, 16) + 1;
	if (f->minus)
		print_ox(buf, c, 'x');
	while (len < f->p)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = '0';
		len++;
	}
}

void	pwidthr_handler(long long n, char *buf, t_flags *f, t_counts *c)
{
	char	ch;
	int		len;

	n < 0 ? n = -n : 0;
	len = (int)ft_nbrlen_base(n, 16) + 3;
	f->p == 0 ? len = 2 : 0;
	ch = ' ';
	f->zero == 1 ? ch = '0' : 0;
	if (f->p > len && !f->zero)
		len = f->p + 2;
	if (f->zero)
		print_ox(buf, c, 'x');
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ch;
		len++;
	}
	!f->zero ? print_ox(buf, c, 'x') : 0;
	pprecision_handler(n, buf, f, c);
}

void	pwidthl_handler(long long n, char *buf, t_flags *f, t_counts *c)
{
	int		len;

	n < 0 ? n = -n : 0;
	len = (int)ft_nbrlen_base(n, 16) + 3;
	if (f->p > len)
		len = f->p + 2;
	while (len < f->m)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = ' ';
		len++;
	}
}

void	handler_p(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	long long	nbr;
	int			len;

	nbr = va_arg(ap, long long);
	nbr == -1 ? nbr = (unsigned int)nbr : 0;
	len = ft_nbrlen_base(nbr, 16) + 3;
	if ((f->m > len || f->p > len) && !f->minus)
		pwidthr_handler(nbr, buf, f, c);
	if ((f->m > len || f->p > len) && !f->minus)
		f->p == 0 ? 0 : convert_hex(buf, c, nbr, 'a');
	else if ((f->m > len || f->p > len) && f->minus)
	{
		pprecision_handler(nbr, buf, f, c);
		f->p == 0 ? 0 : convert_hex(buf, c, nbr, 'a');
		if (f->m > f->p && f->m > len)
			pwidthl_handler(nbr, buf, f, c);
	}
	else
	{
		print_ox(buf, c, 'x');
		f->p == 0 ? 0 : convert_hex(buf, c, nbr, 'a');
	}
}
