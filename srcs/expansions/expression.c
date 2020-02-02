/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 04:54:10 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 06:17:25 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

char	*process_substitution(size_t *i, char *word)
{
	return (NULL);
}

char	*process_parameter(size_t *i, char *word)
{
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
	word[*i] = 0;
	if (!(tmp = get_env(g_env, expression)))
	{
		new_word = ft_vjoin(3, word, "\n", word + a);
		free(word);
	}
	else
	{
		*i += ft_strlen(tmp) - 1;
		new_word = ft_vjoin(3, word, tmp, word + a);
		free(word);
	}
	return (new_word);
}

void	process_expression(char **w)
{
	size_t	i;

	i = 0;
	if (!w || !*w)
		exit(1);
	while ((*w)[i])
	{
		if ((*w)[i] == '$')
		{
			i++;
			if (!(*w)[i] || (*w)[i] == ' ' || (*w)[i] == '\n' \
				|| (*w)[i] == '\t')
				break ;
			if ((*w)[i] == '{')
				*w = process_parameter(&i, *w);
			else if (ft_isalpha((*w)[i]) || (*w)[i] == '_')
				*w = process_simple_parameter(&i, *w);
			else if ((*w)[i] == '(')
				*w = process_substitution(&i, *w);
		}
		i++;
	}
}
