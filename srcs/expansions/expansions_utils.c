/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:43:38 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 04:01:18 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

char	*remove_brace(char *word)
{
	int		i;
	int		j;
	char	tmp[FT_PATH_MAX];
	char	*new_word;

	i = 0;
	j = 0;
	while (word[i] && word[i] != '}')
	{
		if (word[i] == '{')
			i++;
		if (word[i] == '#' && i == 2)
			i++;
		tmp[j] = word[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	new_word = ft_strdup(tmp);
	return (new_word);
}

int		parameter_error(char *word, int index, int act)
{
	if (word[index] == '{' && word[index - 1] != '$')
	{
		ft_putstr_fd("42sh: bad substitution!", 2);
		if (act == 1)
			free(word);
		return (1);
	}
	return (0);
}

char	*error_modifier(char *param, char *word)
{
	free(word);
	free(param);
	ft_putstr_fd("42sh: unrecognized modifier", 2);
	return (ft_strdup(""));
}

char	*get_mod_type(char *word, size_t i, int act)
{
	char	*str;

	str = ft_strnew(3);
	str[0] = word[i];
	if (act == 1)
	{
		if (word[i + 1] == '+' || word[i + 1] == '-'
		|| word[i + 1] == '=' || word[i + 1] == '?')
			str[1] = word[i + 1];
		else
			str[1] = '\0';
	}
	else if (act == 2)
		str[1] = word[i + 1] == '%' ? word[i + 1] : '\0';
	else if (act == 3)
		str[1] = word[i + 1] == '#' ? word[i + 1] : '\0';
	str[2] = '\0';
	return (str);
}

char	*get_expansion_format(char *word)
{
	size_t	a;
	char	*modifier;

	a = 1;
	modifier = NULL;
	while (word[a] && word[a] != '{')
		a++;
	if (word[a - 1] != '$')
		return (modifier);
	if (word[a + 1] == '#')
	{
		get_length_mod(1);
		a++;
	}
	while (word[a] && word[a] != '}')
	{
		a++;
		if (word[a] == ':')
			return (modifier = get_mod_type(word, a, 1));
		else if (word[a] == '%')
			return (modifier = get_mod_type(word, a, 2));
		else if (word[a] == '#')
			return (modifier = get_mod_type(word, a, 3));
	}
	return (modifier);
}
