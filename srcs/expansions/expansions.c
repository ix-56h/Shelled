/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:17:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/09 04:54:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "expansions.h"
#include "sh.h"
#include "libft.h"

int		get_length_mod(int act)
{
	static int mod;

	if (act == 0)
		mod = 0;
	else if (act == 1)
		mod = 1;
	return (mod);
}

int		get_recur_end(int act)
{
	static int rec;

	if (act == 0)
		rec = 0;
	else if (act == 1)
		rec = 1;
	return (rec);
}

char	*expand_tilde(char *w)
{
	size_t	a;
	char	*home;
	char	*new_word;

	new_word = NULL;
	home = NULL;
	a = 0;
	if (w[++a] == '/' || !w[a])
	{
		if (!(home = get_env(g_env, "HOME")))
			home = ft_strdup("");
		if (!(new_word = (ft_strjoin(home, w + 1))))
			exit(1);
		free(w);
		return (new_word);
	}
	return (w);
}

char	*expand_word(char *word)
{
	char *word_len;

	word_len = NULL;
	if (word[0] == '~')
		word = expand_tilde(word);
	get_recur_end(0);
	process_expression(&word);
	if (get_length_mod(2) == 1)
	{
		word_len = ft_itoa(ft_strlen(word));
		get_length_mod(0);
		quote_removal(&word_len);
		free(word);
		return (word_len);
	}
	quote_removal(&word);
	return (word);
}
