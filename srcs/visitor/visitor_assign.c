/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 02:52:26 by akeiflin         ###   ########.fr       */
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

static void		visit_assign_multi(t_node *node)
{
	char *value;
	char *data;

	data = ft_strdup(node->data);
	if ((value = ft_strchr(data, '=')))
	{
		if (ft_strlen(data) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			assign_var(data, value, 0);
		}
	}
	if (node->left)
		visit_assign_multi(node->left);
	free(data);
}

static void		visit_assign_temp(t_node *node, t_job **job, t_io_lists *io)
{
	char *data;
	char *value;
	char *old_value;

	data = ft_strdup(node->data);
	if ((value = ft_strchr(data, '=')))
	{
		if (ft_strlen(data) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			old_value = ft_strdup(get_env(g_set, data));
			assign_var(data, value, 1);
		}
	}
	if (node->left)
		(*g_visit_rules[node->left->tok])(node->left, *io, job);
	restore_env(data, old_value);
	free(old_value);
	free(data);
}

static void		visit_assign_std(t_node *node, int mod)
{
	char *data;
	char *value;

	data = ft_strdup(node->data);
	if ((value = ft_strchr(data, '=')))
	{
		if (ft_strlen(data) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			assign_var(data, value, mod);
		}
	}
	free(data);
}

static int		exec_visit_asign(t_node *node, t_io_lists io, t_job **job)
{
	if (node->left && (!io.piped && !io.redir))
	{
		if (!is_only_assign(node))
			visit_assign_temp(node, job, &io);
		else
			visit_assign_multi(node);
		return (0);
	}
	else
	{
		if (io.piped || io.redir)
			visit_assign_std(node, 1);
		else
			visit_assign_std(node, 0);
		return (!io.redir ? 0 : 1);
	}
}

int				visit_assign_word(t_node *node, t_io_lists io, t_job **job)
{
	int	ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->state == 3)
		grp_cmd_wrapper(&io);
	ret = exec_visit_asign(node, io, job);
	if (node->state == 3)
		dl_del_one_with_data(io.grp_io, free);
	return (ret);
}
