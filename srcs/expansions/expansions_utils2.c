/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:43:38 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 04:01:18 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

int				is_special_param(char c)
{
	if (ft_isdigit(c) || c == '@' || c == '*' || c == '$' || c == '#'
	|| c == '?' || c == '!' || c == '-')
		return (1);
	return (0);
}

int				is_blank(char *last)
{
	int i;

	i = 0;
	while (last[i] == ' ' || last[i] == '\n' || last[i] == '\t')
		i++;
	return (i == ft_strlen(last) ? 1 : 0);
}

void			look_multi_pos_param(char **split, char **word, int i)
{
	int j;

	j = 0;
	ft_strdel(word);
	while (split[j])
		j++;
	if (i < j && i > 0)
	{
		if (ft_strcmp(split[i], ")"))
			*word = ft_strdup(split[i]);
		else
			*word = ft_strdup("");
	}
	else
		*word = ft_strdup("");
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int				braces_error(char c)
{
	if (c == '}' || c == '{')
	{
		ft_putstr_fd("42sh: bad substitution!", 2);
		return (1);
	}
	return (0);
}

void			look_braces_error(char *word, size_t *i)
{
	int		cb;
	int		ob;
	size_t	a;

	a = *i;
	ob = 0;
	cb = 0;
	while (word[ob] != '$')
		ob++;
	ob += 2;
	if (braces_error(word[ob]))
		return ;
	ob = 0;
	while (word[a])
	{
		if (word[a] == '{')
			ob++;
		if (word[a] == '}')
			cb++;
		if (ob && cb && ob == cb)
			break ;
		a++;
	}
	*i = a;
}
