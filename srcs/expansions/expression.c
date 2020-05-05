/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 04:54:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/07 04:08:27 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

char	*process_parameter(size_t *i, char *word)
{
	(void)i;
	return (word);
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

#include <stdio.h>

char	*show_positional_param(void)
{
	int		i;
	int		j;
	char	*str;
	char	*param;

	i = 0;
	j = 0;
	param = get_env(g_set, "@");
	str = ft_strnew(0);
	while (!ft_isalnum(param[i]) && param[i] != ')')
		i++;
	if (param[i] == ')')
		return (str);
	while (param[i] && param[i + 1] != ')')
	{
		str[j] = param[i];
		j++;
		i++;
	}
	return (str);
}

char	*count_param(void)
{
	char	*param;

	param = ft_strdup(get_env(g_set, "#"));
	return (param);
}

char	*look_for_param(int index)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	split = ft_strsplit(get_env(g_set, "@"), ' ');
	if (split[index] && ft_strcmp(split[index], ")"))
		str = ft_strdup(split[index]);
	else
		str = ft_strdup("");
	ft_free(split);
	return (str);
}

char	*get_positional_param(char c)
{
	char	*str;
	char	param[2];

	param[0] = c;
	param[1] = '\0';
	if (c != '0')
		str = look_for_param(ft_atoi(param));
	else
		str = ft_strdup(get_env(g_set, param));
	return (str);
}

void	get_special_param(char **w)
{
	if (ft_isdigit((*w)[1]))
		*w = get_positional_param((*w)[1]);
	else if ((*w)[1] == '@' || (*w)[1] == '*')
		*w = show_positional_param();
	else if ((*w)[1] == '$')
		*w = ft_strdup(get_env(g_set, "$"));
	else if ((*w)[1] == '#')
		*w = count_param();
	else if ((*w)[1] == '?')
		printf("\nINTER\n");
	else if ((*w)[1] == '!')
		printf("\nBANG\n");
}

void	process_expression(char **w)
{
	size_t			i;
	unsigned int	quoted;

	i = 0;
	quoted = 0;
	if (!w || !*w)
		exit(1);
	if (ft_strlen(*w) == 2 && (*w)[i] == '$')
		get_special_param(w);
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
