/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:06 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:40:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_rules.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int			is_opening_class(t_chr_class chr_class)
{
	if (chr_class == CHR_SQUOTE || chr_class == CHR_DQUOTE)
		return (1);
	return (0);
}

t_tokens	token_error(void)
{
	t_tokens new;

	new.data = NULL;
	new.tok = TOK_ERROR;
	return (new);
}

t_tokens	save_token(char *s, int anchor, t_toktype toktype)
{
	t_tokens	new;

	if (anchor > 0)
	{
		if (!(new.data = ft_memalloc(sizeof(char) * (anchor + 1))))
			exit(1);
		ft_strncpy(new.data, s, anchor);
	}
	else
		new.data = NULL;
	if (toktype == TOK_DQUOTE)
	{
		new.dquote = 1; 
		toktype = TOK_WORD;
	}
	new.tok = toktype;
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

t_toktype	get_true_toktype(char *s, t_toktype toktype, int *i)
{
	if (toktype == TOK_OPERATOR)
	{
		if (s[1] && !strncmp(s, "&&", 2))
			return (TOK_AND_IF);
		if (s[1] && !strncmp(s, ";;", 2))
			return (TOK_DSEMI);
		if (!s[1] && !strncmp(s, ";", 1))
			return (TOK_SEMI);
		if (!s[1] && !strncmp(s, "=", 1))
			return (TOK_ASSIGN);
		if (!s[1] && !strncmp(s, "&", 1))
			return (TOK_AND);
	}
	else if (toktype == TOK_PIPE)
	{
		if (s[1] && !strncmp(s, "||", 2))
			return (TOK_OR_IF);
		if (!s[1] && !strncmp(s, "|", 1))
			return (TOK_PIPE);
	}
	else if (toktype == TOK_REDIRECTION)
	{
		if (s[2] && !strcmp(s, "<<-"))
			return (TOK_DLESSDASH);
		if (s[2] && s[2] == '-')
		{
			(*i)--;
			s[2] = 0;
		}
		if (s[1] && !strncmp(s, "<<", 2))
			return (TOK_DLESS);
		if (s[1] && !strncmp(s, ">>", 2))
			return (TOK_DGREAT);
		if (s[1] && !strncmp(s, "<&", 2))
			return (TOK_LESSAND);
		if (s[1] && !strncmp(s, ">&", 2))
			return (TOK_GREATAND);
		if (s[1] && !strncmp(s, "<>", 2))
			return (TOK_LESSGREAT);
		if (s[1] && !strncmp(s, ">|", 2))
			return (TOK_CLOBBER);
		if (!s[1] && !strncmp(s, "<", 1))
			return (TOK_LREDI);
		if (!s[1] && !strncmp(s, ">", 1))
			return (TOK_RREDI);
	}
	return (TOK_ERROR);
}

t_tokens	get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class)
{
	t_chr_class		chr_class = 0;
	t_chr_class		prev_class = 0;
	int				anchor = 0;

	while (s[*i] && ((chr_class = get_chr_class[(unsigned char)s[*i]]) != origin_class
				|| (prev_class == CHR_ESCAPE && toktype == TOK_DQUOTE)))
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
	if (toktype == TOK_SQUOTE)
		toktype = TOK_WORD;
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class)
{
	t_chr_class	chr_class = 0;
	int			anchor = 0;
	
	chr_class = get_chr_class[(unsigned char)s[*i]];
	while (s[*i] &&
			(token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])]
				|| prev_class == CHR_ESCAPE))
	{
		prev_class = chr_class;
		//printf("[%s, '%c', %d]\n", DEBUG_CHR[chr_class], s[*i], anchor);
		anchor++;
		(*i)++;
	}
	if ((toktype == TOK_LPAREN || toktype == TOK_RPAREN) && (anchor += 1))
		(*i)++;
	//printf("{%s, \"%.*s\"}\n", DEBUG_TOKEN[toktype], anchor, s + (*i - anchor));
	return (save_token(s + (*i - anchor), anchor, toktype));
}

t_tokens	get_next_token(char *s)
{
	t_chr_class		chr_class = 0;
	t_toktype		toktype = 0;
	t_tokens		token;
	static int		i = 0;

	if (s[i] == '\0')
		return (save_token(NULL, 0, TOK_EOF));
	if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
		return (token_error());
	if (chr_class == CHR_COMMENT || chr_class == CHR_SP)
	{
		ignore_chr_class(s, &i, chr_class);
		return (get_next_token(s));
	}
	if (!(toktype = get_tok_type[chr_class]))
		return (token_error());
	if (is_opening_class(chr_class))
	{
		i++;
		token = get_sequence_token(s, &i,  toktype, chr_class);
		i++;
	}
	else
	{
		token = get_token(s, &i, toktype, chr_class);
		if (token.tok == TOK_WORD && (s[i] == '>' || s[i] == '<') && (ft_isdigits(token.data)))
			token.tok = TOK_IO_NUMBER;
	}
	//printf("{%s, \"%s\"}\n", DEBUG_TOKEN[token.tok], token.data);
	if (ABSTRACT_TOKEN[token.tok] && !(token.tok = get_true_toktype(token.data, token.tok, &i)))
		return (token_error());
	return (token);
}

//int main(int argc, char *argv[])
//{
//	t_tokens	tok;
//	
//	(void)argc;
//	tok = get_next_token(argv[1]);
//	while (tok.tok != TOK_ERROR && tok.tok != TOK_EOF)
//	{
//		printf("{%s, \"%s\"}\n", DEBUG_TOKEN[tok.tok], tok.data);
//		tok = get_next_token(argv[1]);
//	}
//	if (tok.tok == TOK_ERROR)
//		printf("Syntax error\n");
//	return 0;
//}
