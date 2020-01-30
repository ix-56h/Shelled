/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:02:20 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 13:09:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "libft.h"

int		find_quotes(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"' || *s == '\\')
			return (1);
		s++;
	}
	return (0);
}

char	*find_squotes_end(char *w)
{
	char tmp;

	tmp = w[0];
	while (tmp && tmp != '\'')
	{
		w++;
		tmp = w[0];
	}
	if (tmp == '\0')
		exit(1);
	return (w);
}

char	*remove_squotes(char *w)
{
	erase_char(w);
	w = find_squotes_end(w);
	erase_char(w);
	return (w);
}

char	*remove_quotes(char *w)
{
	char	tmp;

	tmp = *w;
	if (tmp == '\'')
		return (remove_squotes(w));
	else if (tmp == '"')
		return (remove_dquotes(w));
	else if (tmp == '\\')
		return (erase_char(w) + 1);
	else
		return (w + 1);
}

void	quote_removal(char **w)
{
	char	*word;

	if (!w || !(word = *w))
		exit(1);
	if (find_quotes(word))
	{
		while (*word)
			word = remove_quotes(word);
	}
}
