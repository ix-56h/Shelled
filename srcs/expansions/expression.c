/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 04:54:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/02 15:59:52 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

#include <stdio.h>

char	*process_parameter(size_t *i, char *word)
{
	char	*modifier;
	char	*new_word;

	g_test = 0;
	new_word = NULL;
	modifier = get_expansion_format(i, word);
	printf("\nlength mod : %d\n", g_test);
	if (!modifier)
		new_word = process_simple_parameter(i, remove_brace(word));
	else
	{
		new_word = dispatch_exp(word, modifier);
		if (new_word[0] == '$')
			new_word = process_simple_parameter(i, new_word);
	}
	return (g_test == 1 ? ft_itoa(ft_strlen(new_word)) : new_word);
	return (new_word);
}

char	*process_simple_parameter(size_t *i, char *word)
{
	size_t	a;
	char	expression[128];
	char	*new_word;
	char	*tmp;

	tmp = NULL;
	a = *i;
	while (word[a] && (ft_isalpha(word[a]) || ft_isdigit(word[a])))
		a++;
	ft_bzero(expression, 128);
	ft_strncpy(expression, word + *i, (a - *i));
	(*i)--;
	word[*i] = 0;
	if (!(tmp = get_env(g_set, expression)))
	{
		new_word = ft_strjoinf(word, word + a, 1);
		*i -= 1;
	}
	else
	{
		*i += ft_strlen(tmp) - 1;
		new_word = ft_vjoin(3, word, tmp, word + a);
		free(word);
	}
	return (new_word);
}

int		check_dol(size_t *i, char **w)
{
	*i += 1;
	if (!(*w)[*i] || (*w)[*i] == ' ' || (*w)[*i] == '\n' || (*w)[*i] == '\t')
		return (2);
	if ((*w)[*i] == '{')
		*w = process_parameter(i, *w);
	else if (ft_isalpha((*w)[*i]) || (*w)[*i] == '_')
		*w = process_simple_parameter(i, *w);
	else if ((*w)[*i] == '(' && !is_arithmetic((*w) + *i))
		*w = process_substitution(i, *w);
	return (0);
}

void	process_expression(char **w)
{
	size_t			i;
	unsigned int	quoted;

	i = 0;
	quoted = 0;
	if (!w || !*w)
		exit(1);
	while ((*w)[i])
	{
		if ((*w)[i] == '"' && quoted == 2)
			quoted = 0;
		else if ((*w)[i] == '"' && quoted == 0)
			quoted = 2;
		else if ((*w)[i] == '\'' && quoted == 0)
		{
			i = index_end_squote(*w, i);
			continue ;
		}
		else if ((*w)[i] == '$' && check_dol(&i, w) == 2)
			break ;
		i++;
	}
}
