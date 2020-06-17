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
	new_word = NULL;
	if (j > ft_strlen(word))
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

char	*remove_brace(char *word)
{
	int		i;
	int		j;
	char	tmp[FT_PATH_MAX];
	char	*new_word;

	i = 0;
	j = 0;
	ft_bzero(tmp, FT_PATH_MAX);
	if (brace_error(word))
		return (ft_strdup(""));
	while (word[i] && word[i] != '}')
	{
		if (word[i] == '{')
			i++;
		if (word[i] == '#' && i == 2)
			i++;
		tmp[j] = word[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	new_word = ft_strdup(tmp);
	return (new_word);
}

char	*get_closing(char *word, size_t *i, char **last)
{
	size_t	j;
	size_t	a;
	char	*new_word;

	a = *i;
	j = 0;
	new_word = ft_strnew(ft_strlen(word));
	look_braces_error(word, &a);
	while (word[j] && j < a)
	{
		new_word[j] = word[j];
		j++;
	}
	new_word[j] = '\0';
	*i = a + 1;
	*last = get_last_part(word, i);
	free(word);
	return (new_word);
}
