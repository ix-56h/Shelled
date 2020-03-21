/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:04:37 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/16 15:47:30 by akeiflin         ###   ########.fr       */
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

int		sub_is_multiline(char *line, size_t *i, char *finded, char *backslash)
{
	if (line[*i] == '\\' && *finded != '\'')
	{
		if (line[*i + 1] != '\0')
		{
			*i += 2;
			return (0);
		}
	}
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (*finded == 0)
			*finded = line[*i];
		else if (*finded == line[*i])
			*finded = 0;
	}
	if (line[*i] == '#' && *finded == 0)
		return (1);
	if (*i + 1 == ft_strlen(line) && line[*i] == '\\')
		*backslash = 1;
	++(*i);
	return (0);
}

int		is_multiline(t_dl_node *head)
{
	char	finded;
	char	backslash;
	size_t	i;
	char	*line;

	i = 0;
	finded = 0;
	while (head)
	{
		backslash = 0;
		line = ((t_line *)head->data)->line;
		while (line[i])
		{
			if (sub_is_multiline(line, &i, &finded, &backslash))
				return (0);
		}
		i = 0;
		head = head->next;
	}
	return (finded || backslash);
}

int		is_finished(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == ' ')
			--i;
		else
		{
			if (line[i] == '|' && ((i >= 1 && line[i - 1] != '\\') || i == 0))
				return (0);
			else if (line[i] == '&')
			{
				if (i - 1 >= 0 && line[i - 1] == '&')
					return (0);
			}
			else
				return (1);
			--i;
		}
	}
	return (1);
}
