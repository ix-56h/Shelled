/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:48 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 01:01:02 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node		*push_node_left(t_node *to_push, t_node *branch)
{
	t_node *root;

	root = branch;
	while (branch->left)
		branch = branch->left;
	binnode(to_push, branch, branch->right);
	return (root);
}

t_node		*binnode(t_node *left, t_node *mom, t_node *right)
{
	mom->left = left;
	mom->right = right;
	return (mom);
}

t_node		*save_node(t_node *left, t_tokens tok, t_node *right, int id)
{
	t_node	*node;

	node = NULL;
	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->cur_size = 0;
	node->io = -1;
	node->args = NULL;
	if (id == ARGS)
	{
		if (!(node->args = ft_memalloc(sizeof(char *) * ARGS_ARR_SIZE)))
			exit(1);
	}
	node->cur_size = (id == ARGS ? ARGS_ARR_SIZE : 0);
	node->capacity = (id == ARGS ? ARGS_ARR_SIZE - 1 : 0);
	node->cur_i = 0;
	node->state = 0;
	node->left = left;
	node->right = right;
	node->id = id;
	node->tok = tok.tok;
	node->data = tok.data;
	return (node);
}

void		applie_rule_one(char *s, t_tokens *cur)
{
	(void)s;
	if (ft_strcmp(cur->data, "while") == 0)
		cur->tok = TOK_WHILE;
}

t_node		*applie_7b(t_tokens *cur, char *s)
{
	int		tmp;

	if (s[0] == '=')
	{
		applie_rule_one(s, cur);
		return (save_node(NULL, *cur, NULL, ARGS));
	}
	else
	{
		if ((tmp = ft_strichr(s, '=')) > 0\
			&& (s[tmp - 1] != '\'' && s[tmp - 1] != '\\' && s[tmp - 1] != '"'))
		{
			if (!ft_isdigit(s[0]))
				cur->tok = TOK_ASSIGNMENT_WORD;
		}
		else
			applie_rule_one(s, cur);
		return (save_node(NULL, *cur, NULL, ARGS));
	}
	return (NULL);
}
