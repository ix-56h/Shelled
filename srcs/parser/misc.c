/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:48 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/31 14:29:00 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*binnode(t_node *left, t_node *mom, t_node *right)
{
	mom->left = left;
	mom->right = right;
	return (mom);
}

t_node	*save_node(t_node *left, t_tokens tok, t_node *right, int id)
{
	t_node	*node = NULL;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->cur_size = 0;
	node->io = 0;
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

void	applie_rule_one(char *s, t_tokens *cur)
{
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
		//check if word before = form a valid name, if yes, ASSIGMENT_WORD are the toktype
		
		//if ((tok.tok == TOK_WORD) && (ft_strichr(s, '=') > 0) && (cur->squote + cur->dquote) == 0)
		if ((tmp = ft_strichr(s, '=') > 0)) // && isquoted
		{
			// first character of a valid name is not a digit
			if (!ft_isdigit(s[0]))
				cur->tok = TOK_ASSIGNMENT_WORD;
		}
		//else
		//applie rule 1
		return (save_node(NULL, *cur, NULL, ARGS));
	}
	return (NULL);
}

void bst_print_dot_null(char *data, void *key, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    \"%s_%p\" -> null%d;\n", data, key, nullcount);
}

void bst_print_dot_aux(t_node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(stream, "    \"%s_%p\" -> \"%s_%p\";\n", node->data, node, node->left->data, node->left);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->data, node, nullcount++, stream);

    if (node->right)
    {
        fprintf(stream, "    \"%s_%p\" -> \"%s_%p\";\n", node->data, node, node->right->data, node->right);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->data, node, nullcount++, stream);
}

void bst_print_dot(t_node* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    \"%s_%p\";\n", tree->data, tree);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}
