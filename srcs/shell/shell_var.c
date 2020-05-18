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

static char		*show_with_field_split(char *param, char *str, int index)
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
	return (str);
}

static char		*show_positional_param(char c)
{
	int		i;
	int		j;
	char	*str;
	char	*param;

	i = 0;
	j = 0;
	param = get_env(g_set, "@");
	str = ft_strnew(FT_PATH_MAX);
	while (!ft_isalnum(param[i]) && param[i] != ')')
		i++;
	if (param[i] == ')')
		return (str);
	if (c == '*')
		return (show_with_field_split(param, str, i));
	while (param[i] && param[i + 1] != ')')
	{
		str[j] = param[i];
		j++;
		i++;
	}
	return (str);
}

static char		*look_for_param(int index)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	split = ft_strsplit(get_env(g_set, "@"), ' ');
	if (split[index] && ft_strcmp(split[index], ")"))
		str = ft_strdup(split[index]);
	else
		str = ft_strdup("");
	while (split[i])
		free(split[i++]);
	free(split);
	return (str);
}

static char		*get_positional_param(char c)
{
	char	*str;
	char	param[2];

	param[0] = c;
	param[1] = '\0';
	if (c != '0')
		str = look_for_param(ft_atoi(param));
	else
		str = ft_strdup(get_env(g_set, param));
	return (str);
}

void			get_special_param(char ***w)
{
	if (ft_isdigit((**w)[1]))
		**w = get_positional_param((**w)[1]);
	else if ((**w)[1] == '@' || (**w)[1] == '*')
		**w = show_positional_param((**w)[1]);
	else if ((**w)[1] == '$')
		**w = ft_strdup(get_env(g_set, "$"));
	else if ((**w)[1] == '#')
		**w = ft_strdup(get_env(g_set, "#"));
	else if ((**w)[1] == '-')
		ft_bzero(**w, ft_strlen(**w));
	else if ((**w)[1] == '?')
		**w = ft_strdup(get_env(g_set, "?"));
	else if ((**w)[1] == '!')
		**w = ft_strdup(get_env(g_set, "!"));
}
