/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 08:48:38 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/09 22:08:42 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

/*
**  ft_vprint whil print `n' string given in argument
**  ex: ft_vprint(3, "This ", "is ", "a test.");
**          whill print: "This is a test."
*/

void	ft_vprint(int n, ...)
{
	va_list		var;
	int			i;
	char		*working_var;

	i = 0;
	va_start(var, n);
	while (i < n)
	{
		working_var = va_arg(var, char *);
		ft_putstr(working_var);
		++i;
	}
	va_end(var);
}
