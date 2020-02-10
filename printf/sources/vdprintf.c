/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:20:11 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/19 07:35:45 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vdprintf(int fd, const char *str, va_list ap)
{
	t_counts	c;
	char		buf[PF_BUFF_SIZE];

	if (!str)
		return (0);
	ft_bzero(&c, sizeof(t_counts));
	c.fd = fd;
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
