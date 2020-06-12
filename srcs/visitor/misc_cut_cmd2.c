/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cut_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 19:08:10 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/12 19:24:34 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visitor.h"

int		get_end_grouped_cmd(char *cmd, int i)
{
	int		count;

	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' || (cmd[i] == '$' && cmd[i + 1] == '{'))
			i += 2;
		else if (cmd[i] == '{')
		{
			++count;
			++i;
		}
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

int		get_end_subshell(char *cmd, int i)
{
	int		count;

	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '(')
		{
			++count;
			++i;
		}
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

int		get_next_double_cote(char *cmd, int i)
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

int		get_next_cote(char *cmd, int i)
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
