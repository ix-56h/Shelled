#include "parser.h"

void	 free_ast(void)
{

}

void	parse_error(int type)
{
	if (type == 1)
		printf("error\n");
}


/*
t_node	*parse_subshell(char *s, t_tokens *cur)
{
	t_node		*node;

	node = NULL;
	if (cur->tok == TOK_LPAREN)
	{
		*cur = get_next_token(s);
		//if ((node = parse_compound_list(s, cur)))
		if ((node = parse_complete_commands(s, cur)))
		{
			if (cur->tok == TOK_RPAREN)
			{
				node->id = SUBSH;
				*cur = get_next_token(s);
			}
			else
			{
				printf("Error : subshell need to be closed\n");
				node = NULL;
			}
		}
	}
	return (node);
}

*/
