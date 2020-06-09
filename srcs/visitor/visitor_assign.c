/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/02 00:21:54 by akeiflin         ###   ########.fr       */
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

static void		visit_assign_temp(t_node *node, t_job **job)
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
		visit(node->left, job, node->left->data);
	restore_env(data, old_value);
	free(old_value);
	free(data);
}

static void		visit_assign_std(t_node *node)
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
			assign_var(data, value, 0);
		}
	}
	free(data);
}

int				visit_assign_word(t_node *node, t_io_lists io, t_job **job)
{
	dl_append_node((t_dl_node **)&(*job)->list,
						(t_dl_node *)create_process(UNUSED_JOB));
	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->left)
	{
		if (!is_only_assign(node))
			visit_assign_temp(node, job);
		else
			visit_assign_multi(node);
		return (0);
	}
	else
	{
		visit_assign_std(node);
		return (0);
	}
	return (1);
}
