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
	if (chr_class == CHR_SQUOTE || chr_class == CHR_DQUOTE || chr_class == CHR_BQUOTE || chr_class == CHR_LPAREN)
		return (1);
	return (0);
}

t_tokens	token_error(int terr, const char *s)
{
	t_tokens new;

	new.data = NULL;
	new.tok = TOK_ERROR;
	printf(": %s\n", s);
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

int			is_special_char(t_chr_class chr_class, t_chr_class prev_class)
{
	if (prev_class == CHR_ESCAPE)
		return (0);
	else if (chr_class == CHR_DQUOTE || chr_class == CHR_SQUOTE || chr_class == CHR_DOL || chr_class == CHR_BQUOTE)
		return (1);
	return (0);
}

int			lex_sequence(char *s, int *i, int *anchor)
{
	//t_wstat		stat;
	int				ret = 0;
	//ft_bzero(&stat, sizeof(t_wstat));
	//cur = get_cur_seq(s, i, &stat);
	if (s[*anchor] == '\'')
		ret = lex_match_squote(s, i, anchor);
	else if (s[*anchor] == '"')
		ret = lex_match_dquote(s, i, anchor);
	else if (s[*anchor] == '`')
		lex_match_bquote(s, i, anchor);
	else if (s[*anchor] == '$')
		lex_match_dol(s, i, anchor);
	//printf("tokenization error at get end exp\n");
	return (ret);
}

t_tokens	get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class)
{
	t_chr_class	chr_class = 0;
	int			anchor = 0;

	chr_class = get_chr_class[(unsigned char)s[*i]];
	if (is_special_char(chr_class, prev_class) && lex_sequence(s, i, &anchor) == 0)
		return (token_error(0, "blele1"));
	while (s[*i] && (token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])]
				|| prev_class == CHR_ESCAPE))
	{
		if (is_special_char(chr_class, prev_class))
		{
			if (!lex_sequence(s, i, &anchor))
				return (token_error(0, "blele2"));
			continue;
		}
		(toktype == TOK_WORD && prev_class != CHR_ESCAPE && s[*i] == '=') ? (toktype = TOK_ASSIGNMENT_WORD) : 0;
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
		return (token_error(UNRECOGNIZED_CHAR, "unexpected character"));
	if (chr_class == CHR_COMMENT || chr_class == CHR_SP)
	{
		ignore_chr_class(s, &i, chr_class);
		return (get_next_token(s));
	}
	if (!(toktype = get_tok_type[chr_class]))
		return (token_error(UNRECOGNIZED_TOKEN, "unrecognized token"));
	if ((token = get_token(s, &i, toktype, chr_class)).tok == TOK_ERROR)
		return (token);
	if (token.tok == TOK_WORD && (s[i] == '>' || s[i] == '<') && (ft_isdigits(token.data)))
		token.tok = TOK_IO_NUMBER;
	//if (token.tok == TOK_WORD)
		//field_splitting, don't forget to use IFS who's used to determine the character to do splitting
	//printf("{%s, \"%s\"}\n", DEBUG_TOKEN[token.tok], token.data);
	if (ABSTRACT_TOKEN[token.tok] && !(token.tok = get_true_toktype(token.data, token.tok, &i)))
		return (token_error(UNRECOGNIZED_TOKEN, "unrecognized token"));
	return (token);
}

/*int main(int argc, char *argv[])
{
	t_tokens	tok;
	
	(void)argc;
	tok = get_next_token(argv[1]);
	while (tok.tok != TOK_ERROR && tok.tok != TOK_EOF)
	{
		printf("{%s, \"%s\"}\n", DEBUG_TOKEN[tok.tok], tok.data);
		tok = get_next_token(argv[1]);
	}
	if (tok.tok == TOK_ERROR)
		printf("Syntax error\n");
	return 0;
}*/
