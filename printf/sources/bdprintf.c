/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:29:19 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:31:42 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_bdprintf(int buf_size, int fd, const char *str, ...)
{
	t_counts	c;
	char		buf[buf_size];
	va_list		ap;

	if (!str)
		return (0);
	va_start(ap, str);
	ft_bzero(&c, sizeof(t_counts));
	c.fd = fd;
	c.bs = buf_size;
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
