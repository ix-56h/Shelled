/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/03 05:42:20 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"
#include "visitor.h"

#include "ft_printf.h"

char	*exec_substitution(char *tmp)
{
	char *nw = NULL;

	nw = substitution_wrapper(tmp);
	nw = ft_strtrimf(nw);

	return (nw);
}

char	*process_substitution(size_t *i, char *word, char occur)
{
	size_t	y;
	char	*tmp;
	char	*nw;

	(*i)++;
	y = *i;
	while (word[y] && word[y] != occur)
		y++;
	if (!word[y])
		return (0);
	if (word[y] == occur && y > (*i + 1))
	{
		if (!(nw = ft_memalloc((sizeof(char) * y))))
			exit(1);
		ft_strncpy(nw, word + *i, y - 1);
		tmp = exec_substitution(nw);
		free(nw);
		word[*i - (occur == '`' ? 1 : 2)] = 0;
		nw = ft_vjoin(3, word, tmp, word + y + 1);
		free(tmp);
		free(word);
	}
	else
		return (word);
	return (nw);
}
