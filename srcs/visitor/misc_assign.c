/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 03:58:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"
#include "builtins.h"
#include "expansions.h"
#include "ft_printf.h"

void		assign_var(char *data, char *value, int mod)
{
	char	*item;
	char	*expand;

	item = data;
	expand = ft_strdup(value);
	if (value[0] == '$')
		process_expression(&expand);
	if (!mod)
	{
		add_set(item, expand);
		if (!ft_strcmp(item, "HOME"))
			if (!ft_edit_env(g_env, item, expand))
				g_env = add_env(g_env, item, expand);
	}
	else
	{
		if (!ft_edit_env(g_env, item, expand))
			g_env = add_env(g_env, item, expand);
	}
	free(expand);
}

int			is_only_assign(char *data, char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			count++;
		i++;
	}
	return (i == count ? 1 : 0);
}

char		*get_temp_input(char **args)
{
	int		i;
	char	*input;

	i = 1;
	input = ft_strnew(0);
	while (args[i])
	{
		input = ft_strjoinf(input, args[i], 1);
		input = ft_strjoinf(input, " ", 1);
		i++;
	}
	return (input);
}

char		*get_io_input(char *cmd)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	j = 0;
	input = ft_strnew(150);
	while (cmd[i] != '=')
		i++;
	i += 1;
	while (ft_isalnum(cmd[i]))
		i++;
	while (cmd[i] == ' ')
		i++;
	while (i < ft_strlen(cmd))
	{
		input[j] = cmd[i];
		i++;
		j++;
	}
	input[j] = '\0';
	return (input);
}
