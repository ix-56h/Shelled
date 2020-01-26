/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_sequence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:49:04 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/11 18:49:05 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "stack.h"

int	lex_sequence(char *s, int *anchor, t_lifo *stack)
{
	int	ret;

	ret = 0;
	if (s[*anchor] == '\'')
		ret = lex_match_squote(s, anchor, stack);
	else if (s[*anchor] == '"')
		ret = lex_match_dquote(s, anchor, stack);
	else if (s[*anchor] == '`')
		ret = lex_match_command_sub(s, anchor, stack);
	else if (s[*anchor] == '$')
		ret = lex_match_dol(s, anchor, stack);
	return (ret);
}
