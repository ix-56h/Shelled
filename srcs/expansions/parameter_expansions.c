/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions.c                             :+:      :+:    :+:   */
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

char		*remove_pattern(char *param, char *word, size_t index, int act)
{
	int		len;
	char	*new_word;
	size_t	i;

	i = 0;
	len = ft_strlen(param) - ft_strlen(word);
	new_word = ft_strnew(len);
	if (act == 1)
	{
		while (i < index)
		{
			new_word[i] = param[i];
			i++;
		}
	}
	else if (act == 2)
	{
		index = ft_strlen(word);
		while (param[index])
			new_word[i++] = param[index++];
	}
	free(param);
	free(word);
	return (new_word);
}

char		*remove_large_prefix(char *param, char *word)
{
	int	i;

	if (word[0] && get_env(g_set, param))
	{
		if (word[0] == '*' && ft_strlen(param))
		{
			param = ft_strjoinf("$", param, 2);
			param = expand_word(param);
			i = ft_strlen(param) - 1;
			param = remove_prefix_pattern(param, word, i);
			return (param);
		}
		else
		{
			param = remove_small_prefix(param, word);
			return (param);
		}
	}
	free(word);
	param = ft_strjoinf("$", param, 2);
	param = expand_word(param);
	return (param);
}

char		*remove_small_suffix(char *param, char *word)
{
	size_t i;

	if (get_env(g_set, param))
	{
		if (word[0] == '$' && word[1])
			word = expand_word(word);
		param = ft_strjoinf("$", param, 2);
		param = expand_word(param);
		i = ft_strlen(param) - 1;
		while (i > 0)
		{
			if (param[i] == word[0] && look_for_pattern(param, word, i, 1))
			{
				param = remove_pattern(param, word, i, 1);
				return (param);
			}
			i--;
		}
		free(word);
		return (param);
	}
	free(word);
	param = ft_strjoinf("$", param, 2);
	param = expand_word(param);
	return (param);
}

char		*remove_small_prefix(char *param, char *word)
{
	size_t i;

	i = 0;
	if (get_env(g_set, param))
	{
		if (word[0] == '$' && word[1])
			word = expand_word(word);
		param = ft_strjoinf("$", param, 2);
		param = expand_word(param);
		while (param[i])
		{
			if (param[i] == word[0] && look_for_pattern(param, word, i, 2))
			{
				param = remove_pattern(param, word, i, 2);
				return (param);
			}
			i++;
		}
		free(word);
		return (param);
	}
	free(word);
	param = ft_strjoinf("$", param, 2);
	param = expand_word(param);
	return (param);
}

char		*remove_large_suffix(char *param, char *word)
{
	size_t	i;

	if (word[0] && get_env(g_set, param))
	{
		i = ft_strlen(word) - 1;
		if (word[i] == '*' && i > 0)
		{
			param = ft_strjoinf("$", param, 2);
			param = expand_word(param);
			param = remove_suffix_pattern(param, word, i);
			return (param);
		}
		else
		{
			param = remove_small_suffix(param, word);
			return (param);
		}
	}
	free(word);
	param = ft_strjoinf("$", param, 2);
	param = expand_word(param);
	return (param);
}
