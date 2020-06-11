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

int			is_only_assign(t_node *node)
{
	int		i;
	int		count;
	char	*value;

	i = 0;
	count = 0;
	while (node->left)
	{
		if ((value = ft_strchr(node->left->data, '=')))
			count++;
		node = node->left;
		i++;
	}
	if (i == count)
		return (1);
	return (0);
}

void		restore_env(char *data, char *old_value)
{
	if (!old_value[0])
	{
		g_set = del_var(g_set, data);
		g_env = del_var(g_env, data);
	}
	else
	{
		if (ft_strcmp(get_env(g_env, data), old_value) != 0)
			g_env = del_var(g_env, data);
		else if (!ft_edit_env(g_env, data, old_value))
			g_env = add_env(g_env, data, old_value);
		assign_var(data, old_value, 0);
	}
}

void		restore_env_back(t_node *node)
{
	char	*data;
	char	*value;
	char	*old_value;

	data = ft_strdup(node->data);
	value = ft_strchr(data, '=');
	value[0] = '\0';
	value = &value[1];
	old_value = ft_strdup(get_env(g_set, data));
	restore_env(data, old_value);
	free(old_value);
	free(data);
}

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
