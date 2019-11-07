#include "../../incs/parser.h"

t_flags	check_param(char **av)
{
	t_flags f;
	f.debug_all = 0;
	f.ast_draw = 0;
	while (*av)
	{
		if (strcmp(*av, "-debug=all") == 0)
			f.debug_all = 1;
		else if (strcmp(*av, "-ast=draw") == 0)
			f.ast_draw = 1;
		av++;
	}
	return (f);
}

t_node	*binnode(t_node *left, t_node *mom, t_node *right)
{
	mom->left = left;
	mom->right = right;
	return (mom);
}

t_node	*save_node(t_node *left, t_tokens tok, t_node *right, int identifier)
{
	t_node	*node = NULL;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->left = left;
	node->right = right;
	node->id = identifier;
	node->tok = tok.tok;
	node->data = tok.data;
	return (node);
}

/*t_node	*save_args(t_node *left, char **avs, t_node *right)
{
	t_node	*node = NULL;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->left = left;
	node->right = right;
	node->id = ARGS;
	node->args = avs;
	node->tok = tok.tok;
	node->data = tok.data;
	return (node);
}*/

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
        fprintf(stream, "    \"%s_%p\" -> \"%s_%p\";\n", node->data, node, node->left->data, node->left);
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
