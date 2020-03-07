/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/07 04:05:17 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

#include <stdio.h>

char	*use_default_value(char *param, char *word)
{
	char *new_word;

	new_word = NULL;
	if (get_env(g_set, param))
	{
		free(word);
		param = ft_strjoinf("$", param, 2);
		process_expression(&param);
		return (param);
	}
	else
	{
		while (word[0] =='$')
		{
			word = ft_strjoinf(word, "}", 1);
			process_expression(&word);
		}
		free(param);
		return (word);
	}
}

char	*assign_default_value(char *param, char *word)
{
	if (get_env(g_set, param))
	{
		free(word);
		param = ft_strjoinf("$", param, 2);
		process_expression(&param);
		return (param);
	}
	else
	{
		if (word[0] == '$')
			process_expression(&word);
		add_set(param, word);
	}
	free(param);
	return (word);
}

char	*indicate_error(char *param, char *word)
{
	if (get_env(g_set, param))
	{
		free(word);
		param = ft_strjoinf("$", param, 2);
		process_expression(&param);
		return (param);
	}
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(param, 2);
	if (!word[0])
	{
		free(param);
		ft_putstr_fd(": parameter null or not set", 2);
		return (word);
	}
	if (word[0] == '$')
		process_expression(&word);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(word, 2);
	free(param);
	free(word);
	return (NULL);
	return (ft_strdup(""));
}

char	*use_alternative_value(char *param, char *word)
{
	if (!get_env(g_set, param))
	{
		free(word);
		free(param);
		return (ft_strdup(""));
	}
	else
	{
		while (word[0] == '$')
		{
			word = ft_strjoinf(word, "}", 1);
			process_expression(&word);
		}
		free(param);
		return (word);
	}
}

char	*show_string_length(char *param, char *word)   // MOD_LENGTH hors enum
{
	printf("\nSTRING LENGTH\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- show string length -"));
}
