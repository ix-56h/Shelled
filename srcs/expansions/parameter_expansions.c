/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:22:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/28 15:40:08 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*remove_small_suffix(char *param, char *word)
{
	printf("\nHERE 5\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- remove small suffix -"));
}

char	*remove_large_suffix(char *param, char *word)
{
	printf("\nHERE 6\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- remove large suffix -"));
}

char	*remove_small_prefix(char *param, char *word)
{
	printf("\nHERE 7\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- remove small prefix -"));
}

char	*remove_large_prefix(char *param, char *word)
{
	printf("\nHERE 8\n");
	printf("\nparam : |%s|\n", param);
	printf("\nword : |%s|\n", word);
	return (ft_strdup("- remove large prefix -"));
}
