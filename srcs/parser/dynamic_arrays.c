#include "../../incs/parser.h"

char	*push_args(t_node *node, char *s)
{
	if (node->cur_i == node->cur_size)
	{
		int varinutile = 1;
		//realloc
	}

	if (s != NULL)
	{
		node->args[node->cur_i] = s;
		node->cur_i += 1;
	}
	return (node->args[node->cur_i]);
}
