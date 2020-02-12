/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_diou.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 06:10:44 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:29:12 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			convert_int_arg(va_list ap, t_flags f)
{
	long long	ret;

	if (f.length == L_L)
		ret = (long)va_arg(ap, long);
	else if (f.length == L_LL)
		ret = va_arg(ap, long long);
	else if (f.length == L_H)
		ret = (short int)va_arg(ap, int);
	else if (f.length == L_HH)
		ret = (signed char)va_arg(ap, signed int);
	else if (f.length == L_J)
		ret = va_arg(ap, intmax_t);
	else if (f.length == L_Z)
		ret = va_arg(ap, size_t);
	else if (f.c == 'X' || f.c == 'x')
		ret = va_arg(ap, long long);
	else
		ret = va_arg(ap, int);
	return (ret);
}

unsigned long long	convert_u_arg(va_list ap, t_flags f)
{
	unsigned long long	ret;

	if (f.length == L_L)
		ret = va_arg(ap, unsigned long);
	else if (f.length == L_LL)
		ret = va_arg(ap, long long);
	else if (f.length == L_H)
		ret = (unsigned short int)va_arg(ap, unsigned int);
	else if (f.length == L_HH)
		ret = (unsigned char)va_arg(ap, unsigned int);
	else if (f.length == L_J)
		ret = va_arg(ap, uintmax_t);
	else if (f.length == L_Z)
		ret = va_arg(ap, ssize_t);
	else
		ret = va_arg(ap, unsigned int);
	return (ret);
}

void				write_nbr(char *buf, t_counts *c, long long n)
{
	char				s[22];
	int					i;
	unsigned long long	ntm;

	ntm = 0;
	ft_bzero(s, 21);
	i = 0;
	n < 0 ? ntm = (n * -1) : 0;
	if (ntm != 0)
	{
		if (ntm > 9223372036854775807)
			get_number_unsigned(ntm, s, ft_size_digit(ntm) - 2);
		else
			get_number_unsigned(ntm, s, ft_size_digit(ntm) - 1);
	}
	else
		get_number(n, s, ft_size_digit(n) - 1);
	while (s[i])
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = s[i++];
	}
}

void				write_unsigned(char *buf, t_counts *c, unsigned long long n)
{
	char				s[22];
	int					i;
	unsigned long long	n2;

	n2 = n;
	ft_bzero(s, 21);
	i = (n2 == 0 ? 1 : 0);
	while (n2 != 0 && ++i)
		n2 = n2 / 10;
	while (i-- > 0)
	{
		s[i] = n % 10 + '0';
		n /= 10;
	}
	while (s[++i])
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = s[i];
	}
}

void				write_float(char *buf, t_counts *c, long double n, int p)
{
	if (n < 0)
		n *= -1;
	n -= (int)n;
	while (p--)
	{
		n *= 10;
		write_in_buff(buf, (int)n + '0', c);
		n -= (int)n;
	}
}
