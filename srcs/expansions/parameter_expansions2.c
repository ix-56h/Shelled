/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/29 12:59:22 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

#include <stdio.h>

char	*use_default_value(char *param, char *word)
{
	if (get_env(g_env, param))
		return (ft_strjoinf("$", param, 2));
	else
		return (word);
}

char	*assign_default_value(char *param, char *word)
{
	printf("\nHERE 2\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- assign default value -"));
}

char	*indicate_error(char *param, char *word)
{
	if (get_env(g_env, param))
		return (ft_strjoinf("$", param, 2));
	else
	{
		if (!word[0])
			printf("\nparam UNSET / NULL\n");
		else
			printf("\nerror : %s\n", word);
		return (ft_strdup(""));
	}
	return (ft_strdup("- indicate error -"));
}

char	*use_alternative_value(char *param, char *word)
{
	if (!get_env(g_env, param))
		return (ft_strdup(""));
	else
		return (word);
}

char	*show_string_length(char *param, char *word)	// MOD_LENGTH hors enum
{
	printf("\nSTRING LENGTH\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- show string length -"));
}
