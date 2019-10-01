/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/02 01:38:16 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	tokenizer(char *s)
{
	int i = 0;
	t_chr_class chr_class = 0;
	t_toktype token;
	int anchor = 0;

	while (s[i])
	{
		chr_class = get_chr_class[(unsigned char)s[i]];
		token = get_tok_type[chr_class];
		if (token)
		{
			while (s[i] && get_chr_class[(unsigned char)s[i]] == chr_class)
			{
				chr_class = get_chr_class[(unsigned char)s[i]];
				printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[i], anchor);
				anchor++;
				i++;
			}
			printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[token], anchor, s + (i - anchor));
			anchor = 0;
			if (chr_class == CHR_SP)
				i++;
		}
		else
			i++;
	}
}

int	main(int ac, char **av)
{
	tokenizer(av[1]);

	return (0);
}
