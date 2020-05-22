/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/05 02:04:24 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"
#include "visitor.h"

char	*exec_substitution(char *tmp)
{
	char *nw;

	nw = substitution_wrapper(tmp);
	nw = ft_strtrimf(nw);
	return (nw);
}

char	*process_substitution(size_t *i, char *word, char occur)
{
	size_t	y;
	char	*tmp;
	char	*nw;
	size_t	x;

	x = 0;
	(*i)++;
	y = *i;
	while (word[y] && word[y] != occur)
		y++;
	if (!word[y])
		return (word);
	if (word[y] == occur && y > (*i))
	{
		y -= *i;
		if (!(nw = ft_memalloc((sizeof(char) * (y + 1)))))
			exit(1);
		ft_strncpy(nw, word + *i, y);
		tmp = exec_substitution(nw);
		x = ft_strlen(tmp);
		free(nw);
		*i -= (occur == '`' ? 1 : 2);
		word[*i] = 0;
		nw = ft_vjoin(3, word, tmp, word + *i + y + (occur == '`' ? 2 : 3));
		*i += x;
		free(tmp);
		free(word);
	}
	else
		return (word);
	return (nw);
}
