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
	if (get_env(g_set, param))
	{
		free(word);
		param = ft_strjoinf("$", param, 2);
		param = expand_word(param);
		return (param);
	}
	else
	{
		word = expand_word(word);
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
		param = expand_word(param);
		return (param);
	}
	else
	{
		word = expand_word(word);
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
		param = expand_word(param);
		return (param);
	}
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(param, 2);
	if (!word[0])
	{
		free(param);
		ft_putstr_fd(": parameter null or not set\n", 2);
		g_exp_error = 1;
		add_set("?", "1");
		return (word);
	}
	word = expand_word(word);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(word, 2);
	add_set("?", "1");
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
		word = expand_word(word);
		free(param);
		return (word);
	}
}
