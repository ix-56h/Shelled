/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cut_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:24:42 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/18 01:12:35 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visitor.h"

size_t		get_next_semi_col(char *cmd)
{
	size_t		i;

	i = 0;
	while (i < ft_strlen(cmd) && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'')
			i = get_next_cote(cmd, i + 1) + 1;
		else if (cmd[i] == '"')
			i = get_next_double_cote(cmd, i + 1) + 1;
		else if (cmd[i] == '(')
			i = get_end_subshell(cmd, i + 1) + 1;
		else if (cmd[i] == '{')
			i = get_end_grouped_cmd(cmd, i + 1) + 1;
		else if (cmd[i] == ';')
			break ;
		else
			++i;
	}
	return (i);
}

size_t		get_next_and(char *cmd)
{
	size_t		i;

	i = 0;
	while (i < ft_strlen(cmd) && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'')
			i = get_next_cote(cmd, i + 1) + 1;
		else if (cmd[i] == '"')
			i = get_next_double_cote(cmd, i + 1) + 1;
		else if (cmd[i] == '(')
			i = get_end_subshell(cmd, i + 1) + 1;
		else if (cmd[i] == '{')
			i = get_end_grouped_cmd(cmd, i + 1) + 1;
		else if (i > 0 && cmd[i] == '&'
						&& (cmd[i - 1] == '>' || cmd[i - 1] == '<'))
			++i;
		else if (cmd[i] == '&')
			break ;
		else
			++i;
	}
	return (i);
}

char		*cut_command(char *cmd, char act)
{
	size_t	index;
	char	find;
	char	*res;
	size_t	len;

	if (!cmd)
		return (NULL);
	index = get_next_semi_col(cmd);
	if (get_next_and(cmd) < index)
		index = get_next_and(cmd);
	find = cmd[index];
	cmd[index] = '\0';
	res = ft_strdup(cmd);
	cmd[index] = find;
	if (act == 1)
	{
		if (index < ft_strlen(cmd))
			len = ft_strlen(&(cmd[index + 1]));
		else
			len = ft_strlen(&(cmd[index]));
		ft_memcpy(cmd, &(cmd[index + 1]), len);
		cmd[len] = '\0';
	}
	return (res);
}
