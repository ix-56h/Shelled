/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/28 15:36:09 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

#include <stdio.h>

char	*use_default_value(char *param, char *word)
{
	printf("\nHERE 1\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	if (get_env(g_env, param))
		printf("\nIN ENV\n");
	else
		printf("\nOUT ENV\n");
	return (ft_strdup("- use default value -"));
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
	printf("\nHERE 3\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- indicate error -"));
}

char	*use_alternative_value(char *param, char *word)
{
	printf("\nHERE 4\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- use alternative value -"));
}

char	*show_string_length(char *param, char *word)	// MOD_LENGTH hors enum
{
	printf("\nSTRING LENGTH\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- show string length -"));
}
