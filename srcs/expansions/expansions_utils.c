/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:43:38 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/07 04:55:54 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

char	*remove_brace(char *word)
{
	int		i;
	int		j;
	char	test[255];
	char	*new_word;

	i = 0;
	j = 0;
//	new_word = ft_strnew(ft_strlen(word) - 2);
	while (word[i] && word[i] != '}')
	{
		if (word[i] == '{')
			i++;
		if (word[i] == '#' && i == 2)
			i++;
		test[j] = word[i];
		i++;
		j++;
	}
	test[j] = '\0';
	new_word = ft_strdup(test);
	return (new_word);
}

char	*error_test(char *param, char *word)
{
	(void)param;
	(void)word;
	return (ft_strdup("unrecognized modifier"));
}

char	*get_mod_type(char *word, size_t i, int act)
{
	char	*str;

	str = ft_strnew(3);
	str[0] = word[i];
	if (act == 1)
		str[1] = ft_isalnum(word[i + 1]) ? '\0' : word[i + 1];
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
	if (word[a + 1] == '#')
	{
		g_length_mod = 1;
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
