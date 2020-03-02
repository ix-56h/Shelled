/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:43:38 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/02 15:58:34 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

#include <stdio.h>

char	*remove_brace(char *word)	// a chier should be REMAKE
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = ft_strnew(ft_strlen(word) - 2);
	while (word[i] != '}')
	{
		if (word[i] == '{')
			i++;
		if (word[i] == '#' && i == 2)
			i++;
		new_word[j] = word[i];
		i++;
		j++;
	}
	new_word[j] = '\0';
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

char	*get_expansion_format(size_t *i, char *word)
{
	size_t	a;
	char	*modifier;

	a = *i;
	modifier = NULL;
	if (word[a + 1] == '#')
	{
		g_test = 1;
		a++;
	}
	while (word[a])
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
