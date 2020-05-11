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
#include "ft_printf.h"

static void		visitor_assign_exec(t_sh *sh, char *item, char *old_value,
					char *data)
{
	lifo_empty(sh->stack.errors) ? sh->node = parse_program(sh) : 0;
	process_sh(sh);
	add_set(item, old_value);
	free(data);
	free(old_value);
	free_sh(sh);
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
	char	*item;
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
			item = data;
			old_value = ft_strdup(get_env(g_set, item));
			add_set(item, value);
		}
	}
	visitor_assign_exec(&sh, item, old_value, data);
	return (1);
}

int				visit_assign_word(t_node *node, t_io_lists io, t_job **job)
{
	char	*item;
	char	*value;
	char	*data;

	(void)io;
	(void)job;
	data = ft_strdup(node->data);
	if (node->args[1] && visit_assign_temp(data, node->args))
		return (0);
	else if ((value = ft_strchr(data, '=')))
	{
		if (ft_strlen(data) > 1)
		{
			value[0] = '\0';
			value = &value[1];
			item = data;
			add_set(item, value);
			free(data);
			return (0);
		}
	}
	ft_dprintf(2, SHELL_NAME": Assignement word error: %s\n", node->data);
	free(data);
	return (1);
}
