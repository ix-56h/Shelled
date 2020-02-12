/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:30:39 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/15 14:30:40 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *str, ...)
{
	t_counts	c;
	char		buf[PF_BUFF_SIZE];
	va_list		ap;

	va_start(ap, str);
	ft_bzero(&c, sizeof(t_counts));
	c.fd = fd;
	c.bs = PF_BUFF_SIZE;
	while (str[c.s] != '\0')
	{
		if (str[c.s] == '%')
			read_flag(buf, str, &c, ap);
		if (c.b == c.bs)
			flush_buff(buf, &c);
		if (str[c.s] != '\0')
		{
			buf[c.b] = str[c.s];
			c.b++;
			c.s++;
		}
	}
	flush_buff(buf, &c);
	va_end(ap);
	return (c.t);
}
