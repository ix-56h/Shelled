/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordexp_tokenizer.c								:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:40:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void		lex_match_squote(char *s, int *anchor)
{
	while (s[*anchor] && s[*anchor] != '\'')
		*anchor += 1;
	if (!s[*anchor])
	{
		printf("ntm \n");
		return (NULL);
	}
}
