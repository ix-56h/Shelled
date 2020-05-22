/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 05:17:32 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/17 23:27:56 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	shitty_o(t_flags *f, unsigned long long *n2, unsigned long long *nbr)
{
	*n2 = *nbr;
	f->len = 0;
	while (*n2 != 0 && ++f->len)
		*n2 = *n2 / 8;
	*nbr == 0 ? f->len = 1 : 0;
	*nbr == 0 && f->p == 0 && !f->d ? f->len = 0 : 0;
	f->d && f->p <= f->len && *nbr > 0 ? f->len++ : 0;
}

void	write_in_buff(char *buf, char ch, t_counts *c)
{
	if (c->b == c->bs)
		flush_buff(buf, c);
	buf[c->b++] = ch;
}

void	handler(char *buf, t_flags *f, t_counts *c, va_list ap)
{
	if (f->c == 'i' || f->c == 'd')
		handler_i(buf, f, c, ap);
	else if (f->c == 'u')
		handler_u(buf, f, c, ap);
	else if (f->c == 's')
		handler_s(buf, f, c, ap);
	else if (f->c == 'c')
		handler_c(buf, f, c, ap);
	else if (f->c == 'p')
		handler_p(buf, f, c, ap);
	else if (f->c == 'x' || f->c == 'X')
		handler_x(buf, f, c, ap);
	else if (f->c == 'o')
		handler_o(buf, f, c, ap);
	else if (f->c == '%')
		handler_percent(buf, f, c);
	else if (f->c == 'f')
		handler_f(buf, f, c, ap);
}
