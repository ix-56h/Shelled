/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:50:27 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:28:18 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		towp_checker(char c, int check_type)
{
	if (check_type == 1)
	{
		if (c == 'd' || c == 'i' || c == 'c' || c == 's' || c == 'p' || c == 'f'
			|| c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == '%')
			return (1);
	}
	else if (check_type == 2)
	{
		if (c == '#' || c == '-' || c == '+' || c == '0' || c == ' ')
			return (1);
	}
	else if (check_type == 3)
	{
		if (ft_isdigit(c))
			return (1);
	}
	else
	{
		if (c == 'l' || c == 'L' || c == 'h' || c == 'j' || c == 'z')
			return (1);
	}
	return (0);
}

void	flush_buff(char *buf, t_counts *c)
{
	write(c->fd, buf, c->b);
	c->t += c->b;
	c->b = 0;
}

void	read_flag(char *buf, const char *str, t_counts *c, va_list ap)
{
	t_flags	f;

	ft_bzero(&f, sizeof(t_flags));
	f.p = -1;
	if (str[++(c->s)] == '%')
	{
		write_in_buff(buf, '%', c);
		++(c->s);
		return ;
	}
	if (get_opts(&f, str + c->s, c) == -1)
		return ;
	if (f.c != 0)
		handler(buf, &f, c, ap);
}

int		ft_printf(const char *str, ...)
{
	t_counts	c;
	char		buf[PF_BUFF_SIZE];
	va_list		ap;

	if (!str)
		return (0);
	va_start(ap, str);
	ft_bzero(&c, sizeof(t_counts));
	c.fd = 1;
	c.bs = PF_BUFF_SIZE;
	while (str[c.s] != '\0')
	{
		if (str[c.s] == '%')
			read_flag(buf, str, &c, ap);
		else if (str[c.s] == '{')
			read_color(buf, str, &c);
		if (str[c.s] != '\0' && str[c.s] != '%')
		{
			c.b == c.bs ? flush_buff(buf, &c) : 0;
			buf[c.b++] = str[c.s++];
		}
	}
	c.b > 0 ? flush_buff(buf, &c) : 0;
	va_end(ap);
	return (c.t);
}
