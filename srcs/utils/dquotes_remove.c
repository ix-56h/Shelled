/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:32:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/16 02:40:58 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "libft.h"

int		escape_meaning(char c)
{
	if (c == '$' || c == '\'' || c == '"' || c == '\\' || c == '\n')
		return (1);
	return (0);
}

char	*find_dquote_end(char *w)
{
	char tmp;

	tmp = w[0];
	while (tmp && tmp != '"')
	{
		if (tmp == '\\' && escape_meaning(w[1]))
			erase_char(w);
		w++;
		tmp = w[0];
	}
	if (tmp == '\0')
		exit(1);
	return (w);
}

char	*remove_dquotes(char *w)
{
	erase_char(w);
	w = find_dquote_end(w);
	erase_char(w);
	return (w);
}
