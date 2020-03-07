/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 04:14:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/07 04:14:57 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

#include <stdio.h>

char	*get_last_part(char *word, size_t *k)
{
	size_t i;
	size_t j;
	char	tmp[256];
	char	*new_word;

	j = *k;
	i = 0;
	if (g_test == 1)
		return (ft_strdup(""));
	while (word[j])
		tmp[i++] = word[j++];
	tmp[i] = '\0';
	new_word = ft_strdup(tmp);
	g_test = 1;
	return (new_word);
}

char	*get_first_part(char *word)
{
	size_t i;
	size_t j;
	size_t len;
	char *new_word;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '{')
			break;
		i++;
	}
	len = i;
	new_word = ft_strnew(len);
	i = 0;
	while (word[j] && i < len)
		new_word[j++] = word[i++];
	return (new_word);
}

int		check_braces(char *word, size_t *j)
{
	size_t i = 0;
	int obrace = 0;
	int cbrace = 0;

	if (word[2] == '}')
	{
		ft_putstr_fd("42sh: bad substitution 1", 2);
		return (0);
	}
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '{')
		{
			i++;
			obrace++;
		}
		else if ((word[i] == '{' && word[i - 1] != '$')/* || word[i] == '{'*/)
		{
			ft_putstr_fd("42sh: bad substitution 1", 2);
			return (0);
		}
		i++;
	}
	i = 0;
	while (word[i])
	{
		if (word[i] == '}')
			cbrace++;
		if (obrace == cbrace)
			break;
		i++;
	}
	*j = i + 1;
	return (1);
}

char	*process_parameter(size_t *i, char *word)
{
	char	*modifier;
	char	*new_word;
	char	*first;
	char	*last;

	new_word = NULL;
	if (!check_braces(word, i))
		return (ft_strdup(""));
	modifier = get_expansion_format(word);
	first = get_first_part(word);
	last = get_last_part(word, i);
	if (last[0] == '$')
		process_expression(&last);
	if (!modifier)
	{
		new_word = remove_brace(word);
		process_expression(&new_word);
	}
	else
	{
		new_word = dispatch_exp(word, modifier);
		if (first[0])
			new_word = ft_strjoinf(first, new_word, 2);
	}
	if (last[0])
		new_word = ft_strjoinf(new_word, last, 1);
	free(first);
	free(last);
	free(modifier);
	free(word);
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
	{
		*w = process_parameter(i, *w);
		return (1);
	}
	else if (ft_isalpha((*w)[*i]) || (*w)[*i] == '_')
	{
		*w = process_simple_parameter(i, *w);
		return (1);
	}
	else if ((*w)[*i] == '(' && !is_arithmetic((*w) + *i))
	{
		*w = process_substitution(i, *w, ')');
		return (1);
	}
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
		else if ((*w)[i] == '`')
		{
			*w = process_substitution(&i, *w, '`');
			break ;
		}
		else if ((*w)[i] == '$' && check_dol(&i, w) == 1)
			break ;
		i++;
	}
}
