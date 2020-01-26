/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 00:52:26 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

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
		process_expression(&word);
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
	process_expression(&word);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(word, 2);
	free(param);
	free(word);
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
		if (word[0] == '$' && word[1] == '{')
			word = ft_strjoinf(word, "}", 1);
		process_expression(&word);
		free(param);
		return (word);
	}
}
