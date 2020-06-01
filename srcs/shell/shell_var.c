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

static char		*look_for_param(char *word, int index)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	split = ft_strsplit(get_env(g_set, "@"), ' ');
	while (split[i])
		i++;
	if (index > i)
		str = ft_strdup("");
	else if (split[index] && ft_strcmp(split[index], ")"))
		str = ft_strdup(split[index]);
	else
		str = ft_strdup("");
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (str);
}

static char		*get_positional_param(char *word)
{
	char	*str;
	char	param[2];

	param[0] = word[1];
	param[1] = '\0';
	if (word[1] != '0')
		str = look_for_param(word, ft_atoi(param));
	else
		str = ft_strdup(get_env(g_set, param));
	free(word);
	return (str);
}

static char		*show_special_param(char *word)
{
	char *str;
	char param[2];

	param[0] = word[1];
	param[1] = '\0';
	str = ft_strdup(get_env(g_set, param));
	free(word);
	return (str);
}

void			get_special_param(char ***w)
{
	char	*last;
	size_t	i;

	i = 2;
	last = get_last_part(**w, &i);
	if (ft_isdigit((**w)[1]))
		**w = get_positional_param(**w);
	else if ((**w)[1] == '@' || (**w)[1] == '*')
		**w = show_positional_param(**w);
	else if ((**w)[1] == '$' || (**w)[1] == '#'
	|| (**w)[1] == '?' || (**w)[1] == '!' || (**w)[1] == '-')
		**w = show_special_param(**w);
	if (last[0])
		**w = ft_strjoinf(**w, last, 1);
	free(last);
}
