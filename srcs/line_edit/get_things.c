/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:26:01 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/02 21:48:22 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ligne.h"

static int		test_pos(char *buff)
{
	int	i;

	i = 2;
	if (buff[0] != '\033')
		return (0);
	if (buff[1] != '[')
		return (0);
	while (buff[i] != ';')
	{
		if (!ft_isdigit(buff[i]))
			return (0);
		++i;
	}
	++i;
	while (buff[i] != 'R')
	{
		if (!ft_isdigit(buff[i]))
			return (0);
		++i;
	}
	++i;
	if (buff[i] != 0)
		return (0);
	return (1);
}

t_pos			get_cur_pos()
{
	t_pos	pos;
	char buff[20] = {'\0'};
	int i;
	int readsize;

	while (!test_pos(buff))
	{
		ft_bzero(buff, sizeof(char) * 20);
		write(1, "\033[6n", 4);
		readsize = read(0 ,buff ,19);
	}
	i = 2;
	pos.y = ft_atoi(&buff[i]);
	while (i < 20 && buff[i++] != ';');
	pos.x = ft_atoi(&buff[i]);
	return (pos);
}

t_winsize		get_winsize()
{
	t_winsize size;

	if (ioctl(0, TIOCGWINSZ, &size) != -1)
		return (size);
	else
		return ((t_winsize){-1, -1, 0, 0});
}

int				get_last_word_index(t_line *line)
{
	char	*str;
	int		index;

	str = line->line;
	index = line->index;
	while (index > 0 && !ft_isalnum(str[index - 1]))
		--index;
	while (index > 0 && ft_isalnum(str[index - 1]))	
		--index;
	return (index);
}

int				get_next_word_index(t_line *line)
{
	char	*str;
	int		index;

	str = line->line;
	index = line->index;
	while (str[index] && ft_isalnum(str[index]))
		++index;
	while (str[index] && !ft_isalnum(str[index]))	
		++index;
	return (index);
}