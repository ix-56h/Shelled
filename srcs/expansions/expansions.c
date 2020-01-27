/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:17:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/27 03:40:30 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>
#include <sh.h>
#include "libft.h"

char	*insert_str(char *s, int *pos, int anchor, char *str)
{
	char *nw;
	int i;
	
	i = 0;
	nw = NULL;
	if (!(nw = malloc(sizeof(char) * ((ft_strlen(s) + ft_strlen(str)) - anchor))))
		return (NULL);
	while (i != *pos)
	{
		nw[i] = s[i];
		i++;
	}
	while (*str)
	{
		nw[i] = *str;
		str++;
		i++;
	}
	while (s[anchor])
	{
		nw[i] = s[anchor];
		i++;
		anchor++;
	}
	return (nw);
}

char	*expand_tilde(char *w,int *i)
{
	int		a;
	char	*home;
	char	*new_word;

	new_word = NULL;
	home = NULL;
	a = *i;
	if (w[++a] == '/' || !w[a])
	{
		if (!(home = get_env(g_env, "HOME")))
			home = ft_strdup("");
		if (!(new_word = insert_str(w, i, a, home)))
			exit(1);
		free(w);
		*i += ft_strlen(home);
		return (new_word);
	}
	(*i)++;
	return (w);
}

char	*expand_word(char *word)
{
	int		i;

	i = 0;
	// step 1
	if (word[i] == '~')
		word = expand_tilde(word, &i);
	//expand_parameter();
	//expand_substitution();
	//expand_arithmetic();
	
	//step 2
	//field splitting ?
	//gnore step3
	//step 4
	//quote_removal();
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
		if (n->args != NULL)
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
