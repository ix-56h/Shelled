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

static int	look_for_pattern(char *param, char *word, size_t index, int act)
{
	char	pattern[FT_PATH_MAX];
	size_t	i;

	i = 0;
	ft_bzero(pattern, 50);
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

static char	*remove_pattern(char *param, char *word, size_t index, int act)
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

char		*remove_small_suffix(char *param, char *word)
{
	size_t i;

	if (get_env(g_set, param))
	{
		if (word[0] == '$' && word[1])
			process_expression(&word);
		param = ft_strjoinf("$", param, 2);
		process_expression(&param);
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
	process_expression(&param);
	return (param);
}

char		*remove_small_prefix(char *param, char *word)
{
	size_t i;

	i = 0;
	if (get_env(g_set, param))
	{
		if (word[0] == '$' && word[1])
			process_expression(&word);
		param = ft_strjoinf("$", param, 2);
		process_expression(&param);
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
	process_expression(&param);
	return (param);
}
