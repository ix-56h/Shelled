/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_brace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 04:47:24 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 04:02:30 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

char	*get_last_part(char *word, size_t *a)
{
	size_t	i;
	size_t	j;
	char	tmp[FT_PATH_MAX];
	char	*new_word;

	j = *a;
	i = 0;
	if (get_recur_end(2) == 1)
		return (ft_strdup(""));
	while (word[j])
		tmp[i++] = word[j++];
	tmp[i] = '\0';
	new_word = ft_strdup(tmp);
	get_recur_end(1);
	return (new_word);
}

char	*get_first_part(char *word)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_word;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '{')
			break ;
		i++;
	}
	len = i;
	new_word = ft_strnew(len);
	i = 0;
	while (word[j] && i < len)
		new_word[j++] = word[i++];
	return (new_word);
}

int		get_open_brace(char *word)
{
	int i;
	int obrace;

	i = 0;
	obrace = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '{')
		{
			i++;
			obrace++;
		}
		i++;
	}
	return (obrace);
}

int		check_braces(char *word, size_t *a)
{
	size_t	i;
	int		obrace;
	int		cbrace;

	i = 0;
	obrace = 0;
	cbrace = 0;
	if (word[2] == '}')
	{
		ft_putstr_fd("42sh: bad substitution1", 2);
		return (0);
	}
	obrace = get_open_brace(word);
	while (word[i])
	{
		if (word[i] == '}')
			cbrace++;
		if (obrace == cbrace)
			break ;
		i++;
	}
	*a = i + 1;
	return (1);
}
