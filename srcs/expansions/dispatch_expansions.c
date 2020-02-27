/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/27 16:01:24 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

t_exp_param		g_dispatch_string[MOD_MAX] = 	// ajouter au .h ?
{
	{ MOD_USE_DEFAULT, ":-", use_default_value },
	{ MOD_ASSIGN_DEFAULT, ":=", assign_default_value },
	{ MOD_INDICATE_ERROR, ":?", indicate_error },
	{ MOD_USE_ALTERNATIVE, ":+", use_alternative_value },
	{ MOD_RM_SMALL_SUFFIX, "%", remove_small_suffix },
	{ MOD_RM_LARGE_SUFFIX, "%%", remove_large_suffix },
	{ MOD_RM_SMALL_PREFIX, "#", remove_small_prefix },
	{ MOD_RM_LARGE_PREFIX, "##", remove_large_prefix },
	{ MOD_ERROR, ":", error_test }
};

void	ft_dispatch_exp(char *full_word, char *mod)
{
	int		i;
	char	*param;
	char	*word;

	i = -1;
	(void)param;
	word = get_param_and_word(full_word, mod, 0);
	while (++i < 9)
	{
		if (ft_strcmp(mod, g_dispatch_string[i].s) == 0)
			g_dispatch_string[i].ft(NULL, NULL);
	}
}
