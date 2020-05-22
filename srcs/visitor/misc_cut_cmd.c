/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cut_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:24:42 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/20 18:36:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		sub_cut1(char *cmd, int *i)
{
	while (cmd[*i] && cmd[*i] != '\'')
		++(*i);
	++(*i);
}

static void		sub_cut2(char *cmd, int *i)
{
	while (cmd[*i] && cmd[*i] != '"')
	{
		if (cmd[*i] == '\\')
			*i += 2;
		else
			++(*i);
	}
	++(*i);
}

static void		sub_cut3(char *cmd, int *i)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '\\')
			*i += 2;
		else if (cmd[*i] == '\'')
			sub_cut1(cmd, i);
		else if (cmd[*i] == '"')
			sub_cut2(cmd, i);
		else if (cmd[*i] == ';')
			break ;
		else
			++(*i);
	}
}

char			*cut_command(char *cmd, char act)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	sub_cut3(cmd, &i);
	cmd[i] = '\0';
	res = ft_strdup(cmd);
	cmd[i] = ';';
	if (act == 1)
	{
		len = ft_strlen(&(cmd[i + 1]));
		ft_memcpy(cmd, &(cmd[i + 1]), len);
		cmd[len] = '\0';
	}
	return (res);
}
