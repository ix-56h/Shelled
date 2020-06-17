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
	while (word[a] && (ft_isalnum(word[a]) || word[a] == '_'))
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

static char		*process_parameter(size_t *i, char *word)
{
	t_exp_data	exp;
	char		*new_word;

	new_word = NULL;
	quote_removal(&word);
	word = get_closing(word, i, &exp.last);
	if (!word || (word[0] == '$' && !word[1]))
	{
		free(word);
		free(exp.last);
		return (ft_strdup(""));
	}
	exp.modifier = get_expansion_format(word);
	exp.first = get_first_part(word);
	new_word = test_parameter(&exp, word);
	free(exp.first);
	free(exp.last);
	free(exp.modifier);
	free(word);
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
		*i = ft_strlen(*w);
		return (1);
	}
	else if (ft_isalpha((*w)[*i]) || (*w)[*i] == '_')
	{
		*w = process_simple_parameter(i, *w);
		*i = ft_strlen(*w);
		return (1);
	}
	else if ((*w)[*i] == '(' && !is_arithmetic((*w) + *i))
	{
		*w = process_substitution(i, *w, ')');
		*i = ft_strlen(*w);
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
		else if (((**w)[i] == '$' && check_dol(&i, *w) == 1) || (!(**w)[i]))
			continue ;
		i++;
	}
}

void			process_expression(char **w)
{
	if (!w || !*w)
		exit(1);
	if (ft_strlen(*w) == 0)
		return ;
	if (ft_strlen(*w) == 1 && (*w)[0] == '$')
		return ;
	else if (is_special_param((*w)[1]) && (*w)[0] == '$')
		get_special_param(&w);
	expression_loop(&w);
}
