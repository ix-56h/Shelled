/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/08 08:27:55 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>

int			is_opening_class(t_chr_class chr_class)
{
	if (chr_class == CHR_SQUOTE || chr_class == CHR_DQUOTE)
		return (1);
	return (0);
}

t_tokens	*save_token(char *s, int anchor, t_toktype toktype)
{
	t_tokens	*new;

	if (!(new = malloc(sizeof(t_tokens))))
		return (NULL);
	if (anchor > 0)
	{
		if (!(new->tok_literal = malloc(sizeof(char) * (anchor + 1))))
			return (NULL);
		//a remplacer par ft_strncpy
		strncpy(new->tok_literal, s, anchor);
	}
	else
		new->tok_literal = NULL;
	new->tok = toktype;
	new->next = NULL;
	return (new);
}

void	ignore_chr_class(char *s, int *i, t_chr_class chr_class)
{
	if (chr_class == CHR_COMMENT)
	{
		while (s[*i] && s[*i] != '\n')
			(*i)++;
	}
	else
	{
		while (s[*i] && get_chr_class[(unsigned char)s[*i]] == chr_class)
			(*i)++;
	}
}

t_tokens	*get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class)
{
	t_chr_class		chr_class = 0;
	t_chr_class		prev_class = 0;
	int				anchor = 0;

	while (s[*i] && ((chr_class = get_chr_class[s[*i]]) != origin_class || (prev_class == CHR_ESCAPE && toktype == TOK_DQUOTE)))
	{
		prev_class = chr_class;
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	if (!s[*i] || chr_class != origin_class)
	{
		printf("ERROR : Need to close sequence\n");
		exit (0);
	}
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
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
		prev_class = chr_class;
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	*tokenizer(char *s)
{
	int			i = 0;
	t_chr_class	chr_class = 0;
	t_tokens	*begin = save_token(NULL, 0, 0);
	t_tokens	*current = begin;

	while (s[i])
	{
		if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
			exit(0);
		if (chr_class == CHR_SP || chr_class == CHR_COMMENT)
		{
			ignore_chr_class(s, &i, chr_class);
			continue ;
		}
		if (is_opening_class(chr_class))
		{
			i++;
			if (!(current->next = get_sequence_token(s, &i, get_tok_type[chr_class], chr_class)))
				exit (0);
			i++;
		}
		else if (!(current->next = get_token(s, &i, get_tok_type[chr_class], chr_class)))
			exit (0);
		current = current->next;
	}
	current = begin->next;
	free(begin);
	return (current);
}

int	main(int ac, char **av)
{
	t_tokens	*tok_list = NULL;
	if (!(tok_list = tokenizer(av[1])))
	{
		printf("Error: Cant tokenize the string.\n");
		return (0);
	}

	while (tok_list)
	{
		printf("{%s, \"%s\"}\n", DEBUG_TOKEN[tok_list->tok], tok_list->tok_literal);
		tok_list = tok_list->next;
	}

	return (0);
}
