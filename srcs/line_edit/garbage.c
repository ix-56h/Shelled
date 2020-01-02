/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:04:37 by akeiflin          #+#    #+#             */
/*   Updated: 2019/12/31 00:27:48 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ligne.h"
#include "libft.h"

/*
**	Specifier le nombre d'arguments en premier argument
**	envoyer les adresses a free en autre arguments
**	dans l'ordre de free
*/

void	*ft_throw_err_free(int n, ...)
{
	va_list		var;
	int			i;

	i = 0;
	va_start(var, n);
	while (i < n)
	{
		free(va_arg(var, void *));
		++i;
	}
	va_end(var);
	return ((void *)0);
}

int		ft_isallprint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int		is_multiline(t_dl_node *head)
{
	char	finded;
	int		i;
	char	*line;

	i = 0;
	finded = 0;
	while (head)
	{
		line = ((t_line *)head->data)->line;
		while (line[i])
		{
			if (line[i] == '"' || line[i] == '\'')
			{
				if (finded == 0)
					finded = line[i];
				else if (finded == line[i])
					finded = 0;
			}
			++i;
		}
		i = 0;
		head = head->next;
	}
	return (finded);
}