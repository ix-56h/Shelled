/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/02 15:59:21 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

#include <stdio.h>

t_exp_param		g_dispatch_string[MOD_MAX] = 	// ajouter au .h ?
{
	{ MOD_USE_DEFAULT, ":-", use_default_value },			// 1
	{ MOD_ASSIGN_DEFAULT, ":=", assign_default_value },		// 2
	{ MOD_INDICATE_ERROR, ":?", indicate_error },			// 3
	{ MOD_USE_ALTERNATIVE, ":+", use_alternative_value },	// 4
	{ MOD_RM_SMALL_SUFFIX, "%", remove_small_suffix },		// 5
	{ MOD_RM_LARGE_SUFFIX, "%%", remove_large_suffix },		// 6
	{ MOD_RM_SMALL_PREFIX, "#", remove_small_prefix },		// 7
	{ MOD_RM_LARGE_PREFIX, "##", remove_large_prefix },		// 8
	{ MOD_ERROR, ":", error_test }							// 9
};

static char		*get_word(char *full_word, char *mod)
{
	int		i;
	int		j;
	int		len;
	int		index;
	char	*word;

	i = 0;
	j = 0;
	index = mod[1] ? 1 : 0;
	while (full_word[i] != mod[index])
		i++;
	i += 1;
	len = i;
	while (full_word[len] != '}')
		len++;
	len -= i;
	word = ft_strnew(len);
	while (full_word[i] != '}')
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
	while (full_word[len] != mod[0])
		len++;
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
	word = get_word(full_word, mod);
	while (++i < MOD_MAX)
	{
		if (ft_strcmp(mod, g_dispatch_string[i].s) == 0)
			new_word = g_dispatch_string[i].ft(parameter, word);
	}
	return (new_word);
}
