/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cut_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:24:42 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/04 23:00:35 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_end_grouped_cmd(char *cmd, int i)
{
	int		count;

	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '{')
			++count;
		else if (cmd[i] == '}')
		{
			if (count != 0)
				--count;
			else
				break ;
		}
		else
			++i;
	}
	return (i);
}

static int		get_end_subshell(char *cmd, int i)
{
	int		count;

	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '(')
			++count;
		else if (cmd[i] == ')')
		{
			if (count != 0)
				--count;
			else
				break ;
		}
		else
			++i;
	}
	return (i);
}

static int		get_next_double_cote(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '"')
			break ;
		else
			++i;
	}
	return (i);
}

static int		get_next_cote(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'')
			break ;
		else
			++i;
	}
	return (i);
}

static int		get_next_semi_col(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'')
			i = get_next_cote(cmd, ++i) + 1;
		else if (cmd[i] == '"')
			i = get_next_double_cote(cmd, ++i) + 1;
		else if (cmd[i] == '(')
			i = get_end_subshell(cmd, ++i) + 1;
		else if (cmd[i] == '{')
			i = get_end_grouped_cmd(cmd, ++i) + 1;
		else if (cmd[i] == ';')
			break ;
		else
			++i;
	}
	return (i);
}

char			*cut_command(char *cmd, char act)
{
	int		semi_col_index;
	char	*res;
	int		len;

	semi_col_index = get_next_semi_col(cmd);
	cmd[semi_col_index] = '\0';
	res = ft_strdup(cmd);
	cmd[semi_col_index] = ';';
	if (act == 1)
	{
		len = ft_strlen(&(cmd[semi_col_index + 1]));
		ft_memcpy(cmd, &(cmd[semi_col_index + 1]), len);
		cmd[len] = '\0';
	}
	return (res);
}
