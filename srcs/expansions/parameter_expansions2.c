/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/02 14:20:32 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

#include <stdio.h>

char	*use_default_value(char *param, char *word)
{
	if (get_env(g_set, param))
		return (ft_strjoinf("$", param, 2));
	else
		return (word);
}

char	*assign_default_value(char *param, char *word)
{
	if (get_env(g_set, param))
		return (ft_strjoinf("$", param, 2));
	else
		add_set(param, word);
	return (word);
}

char	*indicate_error(char *param, char *word)
{
	if (get_env(g_set, param))
		return (ft_strjoinf("$", param, 2));
	if (!word[0])
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": parameter null or not set", 2);
	}
	else
		return (word);
	return (ft_strdup(""));
}

char	*use_alternative_value(char *param, char *word)
{
	if (!get_env(g_set, param))
		return (ft_strdup(""));
	else
		return (word);
}

char	*show_string_length(char *param, char *word)   // MOD_LENGTH hors enum
{
	printf("\nSTRING LENGTH\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- show string length -"));
}
