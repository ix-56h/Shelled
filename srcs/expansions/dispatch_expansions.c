/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 03:58:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

t_exp_param		g_dispatch_string[MOD_MAX] =
{
	{ MOD_USE_DEFAULT, ":-", use_default_value },
	{ MOD_ASSIGN_DEFAULT, ":=", assign_default_value },
	{ MOD_INDICATE_ERROR, ":?", indicate_error },
	{ MOD_USE_ALTERNATIVE, ":+", use_alternative_value },
	{ MOD_RM_SMALL_SUFFIX, "%", remove_small_suffix },
	{ MOD_RM_LARGE_SUFFIX, "%%", remove_small_suffix },
	{ MOD_RM_SMALL_PREFIX, "#", remove_small_prefix },
	{ MOD_RM_LARGE_PREFIX, "##", remove_small_prefix },
	{ MOD_ERROR, ":", error_modifier }
};

char			*test_parameter(t_exp_data *exp, char *word)
{
	int		i;
	char	*new_word;

	i = 1;
	new_word = NULL;
	if (exp->last[0])
		process_expression(&exp->last);
	if (!exp->modifier)
	{
		new_word = remove_brace(word);
		while (new_word[i++])
			if (parameter_error(new_word, i, 1))
				return (ft_strdup(""));
		process_expression(&new_word);
	}
	else
	{
		new_word = dispatch_exp(word, exp->modifier);
		if (exp->first[0])
			new_word = ft_strjoinf(exp->first, new_word, 2);
	}
	if (exp->last[0])
		new_word = ft_strjoinf(new_word, exp->last, 1);
	return (new_word);
}

static char		*get_word(char *full_word, char *mod)
{
	int		i;
	int		j;
	int		len;
	int		index;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	index = mod[1] ? 1 : 0;
	while (full_word[i] != mod[index])
		i++;
	if (mod[1] && (full_word[i] == '#' || full_word[i] == '%'))
		i += 2;
	else
		i += 1;
	len = i;
	while (full_word && full_word[len] != '}')
		len++;
	len -= i;
	word = ft_strnew(len);
	while (full_word[i] && full_word[i] != '}')
		word[j++] = full_word[i++];
	return (word);
}

static char		*get_param(char *full_word, char *mod)
{
	int		i;
	int		j;
	int		len;
	char	*parameter;

	i = 0;
	j = 0;
	while (full_word[i] != '{')
		i++;
	i += 1;
	if (full_word[i] == '#')
		i++;
	len = i;
	while (full_word[len++] != mod[0])
		if (parameter_error(full_word, len, 0))
			return (ft_strdup(""));
	len -= i;
	parameter = ft_strnew(len);
	while (full_word[i] != mod[0])
		parameter[j++] = full_word[i++];
	return (parameter);
}

char			*dispatch_exp(char *full_word, char *mod)
{
	int		i;
	char	*parameter;
	char	*word;
	char	*new_word;

	i = -1;
	new_word = NULL;
	parameter = get_param(full_word, mod);
	word = parameter[0] ? get_word(full_word, mod) : ft_strdup("");
	while (++i < MOD_MAX)
	{
		if (ft_strcmp(mod, g_dispatch_string[i].s) == 0)
			new_word = g_dispatch_string[i].ft(parameter, word);
	}
	if (!new_word)
		new_word = error_modifier(NULL, NULL);
	return (new_word);
}
