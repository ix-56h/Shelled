#include <unistd.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"
#include "builtins.h"
#include "ft_printf.h"

int		visit_assign_temp(char *data, char **args)
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
	sh.input = ft_strdup(args[1]);
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
	lifo_empty(sh.stack.errors) ? sh.node = parse_program(&sh) : 0;
	process_sh(&sh);
	add_set(item, old_value);
	free(data);
	free(old_value);
	free_sh(&sh);
	return (1);
}

int		visit_assign_word(t_node *node, t_io_lists io, t_job **job)
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
