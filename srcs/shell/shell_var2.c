/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 12:19:58 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 17:11:29 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

static char		*show_with_field_split(char *param, char *str, \
				int index, char *word)
{
	int		i;
	char	*ifs_var;
	char	ifs;

	i = 0;
	ifs_var = ft_strdup(get_env(g_set, "IFS"));
	ifs = ifs_var[0];
	while (param[index] && param[index + 1] != ')')
	{
		str[i] = param[index];
		if (str[i] == ifs)
			str[i] = ' ';
		i++;
		index++;
	}
	free(ifs_var);
	free(word);
	return (str);
}

static char		*show_missing_param(char *word)
{
	free(word);
	return (ft_strdup(""));
}

char			*show_positional_param(char *word)
{
	int		i;
	int		j;
	char	*str;
	char	*param;

	i = 0;
	j = 0;
	param = get_env(g_set, "@");
	if (!param)
		return (show_missing_param(word));
	while (!ft_isalnum(param[i]) && param[i] != ')')
		i++;
	if (param[i] == ')')
		return (show_missing_param(word));
	str = ft_strnew(FT_PATH_MAX);
	if (word[1] == '*')
		return (show_with_field_split(param, str, i, word));
	while (param[i] && param[i + 1] != ')')
	{
		str[j++] = param[i];
		i++;
	}
	str[j] = '\0';
	free(word);
	return (str);
}
