/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 00:31:09 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:00:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_number(long long n, char *s, int i)
{
	while (i >= 0)
	{
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
}

void		get_number_unsigned(unsigned long long n, char *s, int i)
{
	while (i >= 0)
	{
		s[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
}

void		write_str(char *buf, t_counts *c, char *s)
{
	while (*s)
	{
		c->b == c->bs ? flush_buff(buf, c) : 0;
		buf[c->b++] = *s;
		s++;
	}
}

void		convert_hex(char *buf, t_counts *c, long long value, char ch)
{
	char		s[50];
	long long	n;
	int			i;

	ft_bzero(s, 50);
	n = (value < 0) ? -value : value;
	i = ft_nbrlen_base(n, 16) + 1;
	n = (value < 0) ? -value : value;
	while (i--)
	{
		s[i] = (n % 16 < 10) ? n % 16 + '0' : n % 16 + ch - 10;
		n /= 16;
	}
	write_str(buf, c, s);
}

void		print_ox(char *buf, t_counts *c, char ch)
{
	c->b == c->bs ? flush_buff(buf, c) : 0;
	buf[c->b++] = '0';
	c->b == c->bs ? flush_buff(buf, c) : 0;
	buf[c->b++] = ch;
}
