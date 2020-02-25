/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:17:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 15:02:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh.h"
#include "expansions.h"
#include "libft.h"

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
	if (word[0] == '~')
		word = expand_tilde(word);
	process_expression(&word);
	quote_removal(&word);
	return (word);
}

void	process_expansions(t_node *n)
{
	size_t	i;

	if (n == NULL)
		return ;
	if (n->tok == TOK_WORD)
	{
		n->data = expand_word(n->data);
		if (n->args)
		{
			i = 0;
			while (n->args[i])
			{
				n->args[i] = expand_word(n->args[i]);
				i++;
			}
		}
	}
	if (n->left)
		process_expansions(n->left);
	if (n->right)
		process_expansions(n->right);
}
