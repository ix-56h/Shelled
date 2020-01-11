/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 21:22:00 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/11 21:28:14 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

/*
**  ft_vprintfd whil print `n' string given in argument into `fd' filedescriptor
**  ex: ft_vprint(1, 3, "This ", "is ", "a test.");
**          whill print: "This is a test."
*/

void	ft_vprintfd(int fd, int n, ...)
{
	va_list		var;
	int			i;
	char		*working_var;

	i = 0;
	va_start(var, n);
	while (i < n)
	{
		working_var = va_arg(var, char *);
		ft_putstr_fd(working_var, fd);
		++i;
	}
	va_end(var);
}
