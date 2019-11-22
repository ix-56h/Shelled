t_node	*parse_simple_command(char *s, t_tokens *cur)
{
	t_node	*node;
	t_node	*nod2;
	t_node	*args;

	node = NULL;
	nod2 = NULL;
	if ((node = parse_cmd_name(s, cur)))
	{
		args = node;
		while (cur->tok == TOK_WORD)
		{
			push_args(args, cur->data);
			//free
			*cur = get_next_token(s);
		}
		while ((nod2 = parse_cmd_suffix(s, cur)))
			node = binnode(node, nod2, nod2->right);
		while (cur->tok == TOK_WORD)
		{
			push_args(args, cur->data);
			//free
			*cur = get_next_token(s);
		}

	}
	else if ((node = parse_cmd_prefix(s, cur)))
	{
		if ((nod2 = parse_cmd_word(s, cur)))
		{
			args = nod2;
			node = binnode(nod2, node, node->right);
			while ((nod2 = parse_cmd_word(s, cur)))
			{
				push_args(args, nod2->data);
				//free node
			}
			while ((nod2 = parse_cmd_suffix(s, cur)))
				binnode(nod2, node->left, node->left->right);
		}
		else
		{
			while ((nod2 = parse_cmd_prefix(s, cur)))
				binnode(node, nod2, nod2->right);
		}
	}
	return (node);
}

t_node	*parse_cmd_name(char *s, t_tokens *cur)
{
	t_node		*node;
	t_tokens	tok;

	node = NULL;
	if (cur->tok == TOK_WORD)
	{
		if (!strchr(cur->data, '='))
		{
			//applie rule 1 (chekc reserved word associated, if not a reserved word, is word token so return him)
			node = save_node(NULL, *cur, NULL, ARGS);
			*cur = get_next_token(s);
		}
		else
		{
			node = applie_7b(cur, cur->data);
			*cur = get_next_token(s);
		}
	}
	return(node);
}

t_node	*parse_cmd_word(char *s, t_tokens *cur)
{
	t_node		*node;
	char		*s2;

	s2 = cur->data;
	node = NULL;
	if (cur->tok == TOK_WORD)
	{
		node = applie_7b(cur, s2);
		*cur = get_next_token(s);
	}
	return(node);
}

t_node	*parse_cmd_prefix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	node = NULL;
	nod2 = NULL;
	tok = *cur;
	if (tok.tok == TOK_ASSIGNMENT_WORD)
	{
		node = save_node(NULL, tok, NULL, ARGS);
		*cur = get_next_token(s);
		while ((tok = *cur).tok == TOK_ASSIGNMENT_WORD)
		{
			push_args(node, tok.data);
			*cur = get_next_token(s);
			//free
		}
	}
	if ((nod2 = parse_io_redirect(s, cur)))
		node = binnode(node, nod2, nod2->right);
	return (node);
}

t_node	*parse_cmd_suffix(char *s, t_tokens *cur)
{
	t_node		*node;
	t_node		*nod2;
	t_tokens	tok;

	node = NULL;
	nod2 = NULL;
	tok = *cur;
	//if (tok.tok == TOK_WORD)
	//{
	//	node = save_node(NULL, tok, NULL, ARGS);
	//	*cur = get_next_token(s);
	//	while ((tok = *cur).tok == TOK_WORD)
	//	{
	//		push_args(node, tok.data);
	//		*cur = get_next_token(s);
	//		//free
	//	}
	//}
	if ((nod2 = parse_io_redirect(s, cur)))
		node = binnode(node, nod2, nod2->right);
	return (node);
}
