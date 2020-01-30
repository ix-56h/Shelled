/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:55:00 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 11:55:26 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
