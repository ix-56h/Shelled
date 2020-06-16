/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:22:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 03:17:17 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

int			look_for_pattern(char *param, char *word, size_t index, int act)
{
	char	pattern[FT_PATH_MAX];
	size_t	i;

	i = 0;
	ft_bzero(pattern, FT_PATH_MAX);
	if (act == 1)
	{
		while (param[index])
			pattern[i++] = param[index++];
	}
	else if (act == 2)
	{
		while (i < ft_strlen(word))
		{
			pattern[i] = param[i];
			i++;
		}
	}
	if (ft_strcmp(pattern, word) == 0)
		return (1);
	return (0);
}

static int	look_for_prefix_pattern(char *param, char *word, int index)
{
	int		i;
	char	pattern[FT_PATH_MAX];

	i = 0;
	ft_bzero(pattern, FT_PATH_MAX);
	while (param[index])
	{
		pattern[i] = param[index];
		i++;
		index++;
	}
	i = 0;
	index = 0;
	while (word[index] && pattern[i] == word[index])
	{
		i++;
		index++;
	}
	i = ft_strlen(word);
	if (index == i)
		return (1);
	return (0);
}

static int	look_for_suffix_pattern(char *param, char *word, int index)
{
	size_t	i;
	char	pattern[FT_PATH_MAX];

	i = 0;
	ft_bzero(pattern, FT_PATH_MAX);
	while (param[index])
	{
		pattern[i] = param[index];
		i++;
		index++;
	}
	i = 0;
	while (i <= ft_strlen(word) && pattern[i] == word[i])
		i++;
	if (i == ft_strlen(word) || !ft_strcmp(word, pattern))
	{
		free(word);
		return (1);
	}
	free(word);
	return (0);
}

char		*remove_prefix_pattern(char *param, char *word, int index)
{
	int		i;
	char	*new_word;

	i = 0;
	new_word = ft_strnew(ft_strlen(param));
	while (index >= 0)
	{
		if (param[index] == word[1]
		&& look_for_prefix_pattern(param, &word[1], index))
		{
			index += ft_strlen(word) - 1;
			while (param[index])
				new_word[i++] = param[index++];
			free(word);
			free(param);
			return (new_word);
		}
		index--;
	}
	free(word);
	free(new_word);
	return (param);
}

char		*remove_suffix_pattern(char *param, char *word, int i)
{
	int		tmp;
	char	*new_word;

	word[i] = '\0';
	new_word = ft_strnew(ft_strlen(param));
	i = 0;
	while (param[i])
	{
		if (param[i] == word[0] && look_for_suffix_pattern(param, word, i))
		{
			tmp = i;
			i = 0;
			while (param[i] && i < tmp)
			{
				new_word[i] = param[i];
				i++;
			}
			free(param);
			return (new_word);
		}
		i++;
	}
	free(word);
	free(new_word);
	return (param);
}
