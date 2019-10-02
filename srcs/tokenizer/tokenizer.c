/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/02 06:46:03 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>

int			is_opening_class(t_chr_class chr_class)
{
	if (chr_class == CHR_SQUOTE)
		return (1);
	return (0);
}

t_tokens	*save_token(char *s, int anchor, t_toktype toktype)
{
	t_tokens	*new;

	if (!(new = malloc(sizeof(t_tokens)))
		|| !(new->token_literal = malloc(sizeof(char) * (anchor + 1))))
		return (NULL);
	new->token = toktype;
	//a remplacer par ft_strncpy
	strncpy(s, new->token_literal, anchor);
	new->token_literal[anchor] = 0;
	new->next = NULL;
	return (new);
}

void	ignore_chr_class(char *s, int *i, t_chr_class chr_class)
{
	while (s[*i] && get_chr_class[(unsigned char)s[*i]] == chr_class)
	{
		(*i)++;
	}
}

t_tokens	*get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class)
{
	t_chr_class		chr_class = 0;
	t_chr_class		prev_class = 0;
	int				anchor = 0;

	while (s[*i] && ((chr_class = get_chr_class[s[*i]]) != origin_class || prev_class == CHR_ESCAPE))
	{
		prev_class = chr_class;
		(chr_class == CHR_ESCAPE) ? (*i)++ : 0;
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	if (chr_class != origin_class)
	{
		printf("ERROR : Need to close sequence\n");
		exit (0);
	}
	printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	*get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class)
{
	t_chr_class chr_class = 0;
	int anchor = 0;
	
	chr_class = get_chr_class[(unsigned char)s[*i]];
	while (s[*i] &&
		  (token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])] || prev_class == CHR_ESCAPE))
	{
		(chr_class == CHR_ESCAPE) ? (*i)++ : 0;
		prev_class = chr_class;
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

void	tokenizer(char *s)
{
	int i = 0;
	t_chr_class chr_class = 0;
	
	while (s[i])
	{
		chr_class = get_chr_class[(unsigned char)s[i]];
		if (chr_class == CHR_SP)
		{
			ignore_chr_class(s, &i, CHR_SP);
			continue ;
		}
		if (is_opening_class(chr_class))
		{
			i++;
			if (!get_sequence_token(s, &i, get_tok_type[chr_class], chr_class))
				exit (0);
			i++;
		}
		else if (!get_token(s, &i, get_tok_type[chr_class], chr_class))
			exit (0);
	}
}

int	main(int ac, char **av)
{
	tokenizer(av[1]);

	return (0);
}
