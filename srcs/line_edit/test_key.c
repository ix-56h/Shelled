/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:05:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/14 17:12:57 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_ctrl_left(char *buff)
{
	if (ft_strcmp(buff, "\x1b\x1b[D") == 0)
		return (1);
	if (ft_strcmp(buff, "\x1b""b") == 0)
		return (1);
	if (ft_strcmp(buff, "\033[1;5D") == 0)
		return (1);
	return (0);
}

int	is_ctrl_right(char *buff)
{
	if (ft_strcmp(buff, "\x1b\x1b[C") == 0)
		return (1);
	if (ft_strcmp(buff, "\x1b""f") == 0)
		return (1);
	if (ft_strcmp(buff, "\033[1;5C") == 0)
		return (1);
	return (0);
}

int	is_ctrl_up(char *buff)
{
	if (ft_strcmp(buff, "\x1b\x1b[A") == 0)
		return (1);
	if (ft_strcmp(buff, "\x1b""[a") == 0)
		return (1);
	if (ft_strcmp(buff, "\033[1;5A") == 0)
		return (1);
	return (0);
}

int	is_ctrl_down(char *buff)
{
	if (ft_strcmp(buff, "\x1b\x1b[B") == 0)
		return (1);
	if (ft_strcmp(buff, "\x1b""[b") == 0)
		return (1);
	if (ft_strcmp(buff, "\033[1;5B") == 0)
		return (1);
	return (0);
}
