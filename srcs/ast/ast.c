/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:01:43 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/11 15:10:07 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "lexer.h"
#include "ast.h"
#include <stdio.h>

t_ast		*create_node(t_tokens *token)
{
	t_ast	*node = NULL;

	if (GRAMMAR_RULES[token->tok][token->next->tok][token->next->next->tok])
		printf("yes\n");
	else
		printf("error\n");
	return (node);
}
