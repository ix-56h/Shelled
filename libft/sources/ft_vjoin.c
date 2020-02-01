/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 08:47:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/01 04:49:05 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

/*
**  ft_vjoin whil concatenate `n' string given in argument
**  ex: ft_vjoin(3, "This ", "is ", "a test.");
**          whill return: "This is a test."
**  return the new malloced string
*/

char	*ft_vjoin(int n, ...)
{
	va_list		var;
	int			i;
	char		*working_var;
	char		*str;

	str = NULL;
	i = 0;
	va_start(var, n);
	while (i < n)
	{
		working_var = va_arg(var, char *);
		str = ft_strljoin(str, working_var, FIRST);
		++i;
	}
	va_end(var);
	return (str);
}
