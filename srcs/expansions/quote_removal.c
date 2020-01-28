/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:02:20 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/28 08:10:38 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <sh.h>
#include "libft.h"

//The quote characters ( <backslash>, single-quote, and double-quote) that were present in the original word shall be removed unless they have themselves been quoted.

char	*squote_remove(char *w, size_t *i)
{
	size_t	j;
	size_t	y;
	char	*new_word;
	char	*tmp;

	j = 0;
	y = 0;
	new_word = NULL;
	tmp = NULL;
	
	if (*i == 0)
		new_word = ft_strdup("");
	else if (!(new_word = ft_strsub(w, 0, *i)))
		exit(1);
	y = *i + 1;
	while (w[y + j] && w[y + j] != '\'')
		j++;
	if (j > 0)
	{
		if (!(tmp = ft_strsub(w, y, j))
			|| (!(new_word = ft_strjoinf(new_word, tmp, 3))))
			exit(1);
	}
	else if (!new_word[0] && j == 0 && !w[y + 1])
		return (new_word);
	if (!(new_word = ft_strjoinf(new_word, w + (y + j), 1)))
			exit(1);
	return (new_word);
}

//char	*dquote_remove(char *w, size_t *i);

char	*quote_removal(char *w)
{
	size_t			i;
	unsigned int	escape;
	char			*tmp;
	
	tmp = w;
	escape = 0;
	i = 0;
	while (w[i])
	{
		if (w[i] == '\\' && !escape)
			escape = 1;
		else if (w[i] == '\\')
		{
			//escape(w, &i);
			escape = 0;
		}
		else if (w[i] == '\'' && !escape)
		{
			w = squote_remove(w, &i);
			free(tmp);
			tmp = w;
			i = 0;
			continue ;
		}
		//else if (w[i] == '"' && !escape)
		//	dquote_remove(w, &i);
		i++;
	}
	return (w);
}
