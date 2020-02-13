/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:31:37 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/14 00:32:55 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_rules.h"
#include "error_handler.h"

int			is_opening_class(t_chr_class chr_class)
{
	if (chr_class == CHR_SQUOTE || chr_class == CHR_DQUOTE
		|| chr_class == CHR_BQUOTE || chr_class == CHR_LPAREN)
		return (1);
	return (0);
}

t_tokens	token_error(int type, t_lifo *stack, char c)
{
	t_tokens	new;
	char		*near;
	char		buf[2];

	near = NULL;
	buf[0] = c;
	buf[1] = 0;
	if (!(near = ft_strdup(buf)))
		exit(2);
	if (type > 0)
		error_push(stack, type, near);
	new.data = near;
	new.tok = TOK_ERROR;
	return (new);
}

t_tokens	save_token(char *s, int anchor, t_toktype toktype)
{
	t_tokens	new;

	if (toktype == TOK_EOF)
	{
		if (!(new.data = ft_strdup("EOF")))
			exit(1);
	}
	else if (anchor > 0)
	{
		if (!(new.data = ft_memalloc(sizeof(char) * (anchor + 1))))
			exit(1);
		ft_strncpy(new.data, s, anchor);
	}
	else
		new.data = NULL;
	new.anchor = anchor;
	new.tok = toktype;
	return (new);
}

void		ignore_chr_class(char *s, int *i, t_chr_class chr_class)
{
	if (chr_class == CHR_COMMENT)
	{
		while (s[*i] && s[*i] != '\n')
			(*i)++;
	}
	else
	{
		while (s[*i] && g_get_chr_class[(unsigned char)s[*i]] == chr_class)
			(*i)++;
	}
}

int			is_special_char(t_chr_class chr_class, t_chr_class prev_class)
{
	if (prev_class == CHR_ESCAPE)
		return (0);
	else if (chr_class == CHR_DQUOTE || chr_class == CHR_SQUOTE
			|| chr_class == CHR_DOL || chr_class == CHR_BQUOTE)
		return (1);
	return (0);
}
