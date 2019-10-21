/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 10:09:50 by niguinti          #+#    #+#             */
/*   Updated: 2019/08/10 12:02:29 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int		ft_get_line(char **line, char **str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if ((*str)[0] == '\n')
	{
		if (!(*line = ft_strdup("\n"))
			|| !(tmp = ft_strsub(*str, 1, ft_strlen(*str))))
			return (-1);
		free(*str);
		*str = tmp;
		return (1);
	}
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (!(*line = ft_strsub(*str, 0, i)))
		return (-1);
	if (!(tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i)))
		return (-1);
	free(*str);
	*str = tmp;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret_read;
	static char	*str;

	if (fd < 0 || fd > 1024 || !line)
		return (-1);
	(!str) ? str = ft_strnew(0) : 0;
	while ((ret_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret_read] = 0;
		if (!(str = ft_strjoinf(str, buf, 1)))
			return (-1);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret_read < 0 || !ft_get_line(line, &str))
		return (-1);
	if ((*line)[0] == '\n' && !((*line)[0] = 0))
		return (1);
	if (ret_read == 0 && (!(**line) && !str))
		return (0);
	return (1);
}
