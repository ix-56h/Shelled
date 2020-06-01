/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:29:55 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/13 01:46:47 by ezonda           ###   ########.fr       */
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

void			assign_var(char *data, char *value, int mod)
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

static int		is_only_assign(char *data, char **args)
{
	int i;
	int count;

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

static int		visitor_assign_exec(t_sh *sh, char *item, char *old_value,
					char *data)
{
	lifo_empty(sh->stack.errors) ? sh->node = parse_program(sh) : 0;
	process_sh(sh);
	if (!ft_edit_env(g_env, item, old_value))
		g_env = add_env(g_env, item, old_value);
	add_set(item, old_value);
	free(old_value);
	free(data);
	free_sh(sh);
	return (1);
}

static char		*get_temp_input(char **args)
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

static int		visit_assign_temp(char *data, char **args)
{
	t_sh	sh;
	char	*value;
	char	*old_value;

	sh.f.ast_draw = 0;
	if (!(sh.stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return (0);
	if (!(sh.stack.here_docs = fifo_creator(20, sizeof(t_node*))))
		return (0);
	sh.input = get_temp_input(args);
	sh.tok = get_next_token(sh.input, sh.stack.errors);
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
	return (visitor_assign_exec(&sh, data, old_value, data));
}

int				visit_assign_multi(char *data, char **args)
{
	int		i;
	char	*value;
	char	*item;
	char	*expand;

	i = 0;
	while (args[i])
	{
		if ((value = ft_strchr(args[i], '=')))
		{
			if (ft_strlen(args[i]) > 1)
			{
				value[0] = '\0';
				value = &value[1];
				item = args[i];
				expand = ft_strdup(value);
				if (value[0] == '$')
					process_expression(&expand);
				add_set(item, expand);
				free(expand);
			}
		}
		i++;
	}
	free(data);
	return (0);
}

int				visit_assign_word(t_node *node, t_io_lists io, t_job **job)
{
	char	*value;
	char	*data;

	(void)io;
	(void)job;
	data = ft_strdup(node->data);
	if (node->args[1] && is_only_assign(data, node->args))
		return (visit_assign_multi(data, node->args));
	else if (node->args[1] && visit_assign_temp(data, node->args))
		return (0);
	else if ((value = ft_strchr(data, '=')))
	{
		if (ft_strlen(data) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			assign_var(data, value, 0);
			free(data);
			return (0);
		}
	}
	ft_dprintf(2, SHELL_NAME": Assignement word error: %s\n", node->data);
	free(data);
	return (1);
}
