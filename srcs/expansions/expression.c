/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 04:14:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 04:56:10 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

char			*process_simple_parameter(size_t *i, char *word)
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
#include <stdio.h>
static char		*process_parameter(size_t *i, char *word)
{
	t_exp_data	exp;
	char		*new_word;

	new_word = NULL;
	if (!check_braces(word, i))
		return (ft_strdup(""));
//	printf("\ni : %ld\n", *i);
	exp.modifier = get_expansion_format(word);
	exp.first = get_first_part(word);
	exp.last = get_last_part(word, i);
	new_word = test_parameter(&exp, word);
	free(exp.first);
	free(exp.last);
	free(exp.modifier);
	free(word);
//	printf("\nnew word : |%s|\n", new_word);
	return (new_word);
}

static int		check_dol(size_t *i, char **w)
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

static void		expression_loop(char ***w)
{
	size_t			i;
	unsigned int	quoted;

	i = 0;
	quoted = 0;
	while ((**w)[i])
	{
		if ((**w)[i] == '"' && quoted == 2)
			quoted = 0;
		else if ((**w)[i] == '"' && quoted == 0)
			quoted = 2;
		else if ((**w)[i] == '\'' && quoted == 0)
		{
			i = index_end_squote(**w, i);
			continue ;
		}
		else if ((**w)[i] == '`')
		{
			**w = process_substitution(&i, **w, '`');
			break ;
		}
		else if ((**w)[i] == '$' && check_dol(&i, *w) == 1)
			break ;
		i++;
	}
}

void			process_expression(char **w)
{
	if (!w || !*w)
		exit(1);
	if (ft_strlen(*w) == 1 && (*w)[0] == '$')
		return ;
	else if (ft_strlen(*w) == 2 && (*w)[0] == '$')
		get_special_param(&w);
	expression_loop(&w);
//	printf("\nfinal word : |%s|\n", *w);
}
