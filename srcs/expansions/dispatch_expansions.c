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
	{ MOD_RM_LARGE_SUFFIX, "%%", remove_large_suffix },
	{ MOD_RM_SMALL_PREFIX, "#", remove_small_prefix },
	{ MOD_RM_LARGE_PREFIX, "##", remove_large_prefix },
	{ MOD_ERROR, ":", error_modifier }
};

static char		*get_word_end(char *word, char *full_word)
{
	int		i;
	int		j;
	char	last[256];

	i = 0;
	j = 0;
	ft_bzero(last, 256);
	while (full_word[i] && full_word[i] != '}')
		i++;
	if (full_word[i] && !full_word[i + 1])
		return (word);
	while (full_word[i])
	{
		last[j] = full_word[i];
		i++;
		j++;
	}
	word = ft_strjoinf(word, last, 1);
	return (word);
}

static char		*get_word(char *full_word, char *mod)
{
	int		i;
	int		j;
	int		index;
	char	*word;
	size_t	len;

	i = 0;
	j = 0;
	index = mod[1] ? 1 : 0;
	while (full_word[i] != mod[index])
		i++;
	if (mod[1] && (full_word[i] == '#' || full_word[i] == '%'))
		i += 2;
	else
		i += 1;
	len = i;
	if (!full_word[len])
		return (ft_strdup(""));
	while (len < ft_strlen(full_word) && full_word[len] != '}')
		len++;
	len -= i;
	word = ft_strnew(len);
	while (full_word[i] && full_word[i] != '}')
		word[j++] = full_word[i++];
	return (get_word_end(word, full_word));
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
	char	*var;
	char	*parameter;
	char	*word;
	char	*new_word;

	i = -1;
	new_word = NULL;
	parameter = get_param(full_word, mod);
	word = parameter[0] ? get_word(full_word, mod) : ft_strdup("");
	word = expand_word(word);
	var = ft_strdup(parameter);
	if (ft_isalldigit(var))
		add_set(var, look_for_param(ft_atoi(var)));
	while (++i < MOD_MAX)
	{
		if (ft_strcmp(mod, g_dispatch_string[i].s) == 0)
			new_word = g_dispatch_string[i].ft(parameter, word);
	}
	if (!new_word)
		new_word = error_modifier(NULL, NULL);
	if (ft_isalldigit(var))
		g_set = del_var(g_set, var);
	free(var);
	return (new_word);
}
