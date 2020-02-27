/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:40:56 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/27 16:02:17 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*use_default_value(char *param, char *word)
{
	printf("\nHERE 1\n");
	(void)param;
	(void)word;
	return (NULL);
}

char	*assign_default_value(char *param, char *word)
{
	printf("\nHERE 2\n");
	(void)param;
	(void)word;
	return (NULL);
}

char	*indicate_error(char *param, char *word)
{
	printf("\nHERE 3\n");
	(void)param;
	(void)word;
	return (NULL);
}

char	*use_alternative_value(char *param, char *word)
{
	printf("\nHERE 4\n");
	(void)param;
	(void)word;
	return (NULL);
}

char	*show_string_length(char *param, char *word)	// MOD_LENGTH hors enum
{
	printf("\nHERE 5\n");
	(void)param;
	(void)word;
	return (NULL);
}
