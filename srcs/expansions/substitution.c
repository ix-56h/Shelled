/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/15 20:50:15 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"
#include "visitor.h"

static char		*exec_substitution(char *tmp)
{
	char *nw;

	nw = substitution_wrapper(tmp);
	nw = ft_strtrimf(nw);
	free(tmp);
	return (nw);
}

static size_t	get_first_pos(size_t *i, char *word, char occur)
{
	size_t	y;
	int		t;

	t = 0;
	y = *i;
	while (word[y] && (word[y] != occur || t > 0))
	{
		if (occur == ')' && word[y] == '(')
			t += 1;
		else if (word[y] == occur && t > 0)
			t--;
		else if (word[y] == occur && t == 0)
			break ;
		y++;
	}
	if (!word[y])
		return (0);
	return (y);
}

static size_t	get_new_pos(size_t *i, char *tmp, char *word)
{
	size_t	x;

	x = ft_strlen(tmp);
	*i += x;
	free(tmp);
	free(word);
	return (*i);
}

char			*process_substitution(size_t *i, char *word, char occur)
{
	size_t	y;
	char	*tmp;
	char	*nw;

	(*i)++;
	y = get_first_pos(i, word, occur);
	if (y == 0)
		return (word);
	if (word[y] == occur && y > (*i))
	{
		y -= *i;
		if (!(nw = ft_memalloc((sizeof(char) * (y + 1)))))
			exit(1);
		ft_strncpy(nw, word + *i, y);
		tmp = exec_substitution(nw);
		*i -= (occur == '`' ? 1 : 2);
		word[*i] = 0;
		nw = ft_vjoin(3, word, tmp, word + *i + y + (occur == '`' ? 2 : 3));
		*i = get_new_pos(i, tmp, word);
	}
	else
		return (word);
	return (nw);
}
