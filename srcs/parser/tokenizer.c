/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:36:10 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/19 06:36:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "tokenizer_rules.h"
#include "error_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int			is_opening_class(t_chr_class chr_class)
{
	if (chr_class == CHR_SQUOTE || chr_class == CHR_DQUOTE || chr_class == CHR_BQUOTE || chr_class == CHR_LPAREN)
		return (1);
	return (0);
}

t_tokens	token_error(int type, t_stack *stack, char c)
{
	t_tokens	new;
	char		near[2];

	near[0] = c;
	near[1] = 0;
	if (type > 0)
		error_push(stack, type, near);
	new.data = NULL;
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

t_toktype	check_operator(char *s, size_t len, int *i)
{
	t_toktype	ret;

	ret = 0;
	if (s[1] && !strncmp(s, "&&", 2))
	{
		*i -= (len - 2);
		ret = TOK_AND_IF;
	}
	else if (s[1] && !strncmp(s, ";;", 2))
	{
		*i -= (len - 2);
		ret = TOK_DSEMI;
	}
	else if (!s[1] && !strncmp(s, ";", 1))
	{
		*i -= (len - 1);
		ret = TOK_SEMI;
	}
	else if (!s[1] && !strncmp(s, "&", 1))
	{
		*i -= (len - 1);
		ret = TOK_AND;
	}
	return (ret);
}

t_toktype	check_pipe(char *s, size_t len, int *i)
{
	t_toktype	ret;

	ret = 0;
	if (s[1] && !strncmp(s, "||", 2))
	{
		*i -= (len - 2);
		ret = TOK_OR_IF;
	}
	else if (!s[1] && !strncmp(s, "|", 1))
	{
		*i -= (len - 1);
		ret = TOK_PIPE;
	}
	return (ret);
}

t_toktype	check_redirections(char *s, size_t len, int *i)
{
		t_toktype	ret;

		ret = 0;
		if (!strcmp(s, "<<-"))
		{
			*i -= (len - 3);
			ret = TOK_DLESSDASH;
		}
		else if (!strncmp(s, "<<", 2))
		{
			*i -= (len - 2);
			ret = TOK_DLESS;
		}
		else if (!strncmp(s, ">>", 2))
		{
			*i -= (len - 2);
			ret = TOK_DGREAT;
		}
		else if (!strncmp(s, "<&", 2))
		{
			*i -= (len - 2);
			ret = TOK_LESSAND;
		}
		else if (!strncmp(s, ">&", 2))
		{
			*i -= (len - 2);
			ret = TOK_GREATAND;
		}
		else if (!strncmp(s, "<>", 2))
		{
			*i -= (len - 2);
			ret = TOK_LESSGREAT;
		}
		else if (!strncmp(s, ">|", 2))
		{
			*i -= (len - 2);
			ret = TOK_CLOBBER;
		}
		else if (!strncmp(s, "<", 1))
		{
			*i -= (len - 1);
			ret = TOK_LREDI;
		}
		else if (!strncmp(s, ">", 1))
		{
			*i -= (len - 1);
			ret = TOK_RREDI;
		}
		return (ret);
}

t_toktype	get_true_toktype(char *s, t_toktype toktype, int *i)
{
	size_t	l;
	int		ret;

	ret = TOK_ERROR;
	l = ft_strlen(s);
	if (toktype == TOK_OPERATOR)
		ret = check_operator(s, l, i);
	else if (toktype == TOK_PIPE)
		ret = check_pipe(s, l, i);
	else if (toktype == TOK_REDIRECTION)
		ret = check_redirections(s, l, i);
	return (ret);
}

int			is_special_char(t_chr_class chr_class, t_chr_class prev_class)
{
	if (prev_class == CHR_ESCAPE)
		return (0);
	else if (chr_class == CHR_DQUOTE || chr_class == CHR_SQUOTE || chr_class == CHR_DOL || chr_class == CHR_BQUOTE)
		return (1);
	return (0);
}

t_tokens	get_token(char *s, int *i, t_chr_class chr_class, t_stack *stack)
{
	t_chr_class	prev_class = chr_class;
	int			anchor = 0;
	t_toktype	toktype = get_tok_type[prev_class];

	//chr_class = get_chr_class[(unsigned char)s[*i]];
	if (is_special_char(chr_class, prev_class) && lex_sequence(s, i, &anchor, stack) == 0)
		return (token_error(0, stack, 0));
	while (s[*i] && (token_chr_rules[toktype][(chr_class = get_chr_class[(unsigned char)s[*i]])]
				|| prev_class == CHR_ESCAPE))
	{
		if (is_special_char(chr_class, prev_class))
		{
			if (!lex_sequence(s, i, &anchor, stack))
				return (token_error(0, stack, 0));
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

t_tokens	get_next_token(char *s, t_stack *stack)
{
	t_chr_class		chr_class = 0;
	t_toktype		toktype = 0;
	t_tokens		token;
	static int		i = 0;

	if (s[i] == '\0')
		return (save_token(NULL, 0, TOK_EOF));
	if (!(chr_class = get_chr_class[(unsigned char)s[i]]))
		return (token_error(UNRECOGNIZED_TOKEN, stack, s[i]));
	if (chr_class == CHR_COMMENT || chr_class == CHR_SP)
	{
		ignore_chr_class(s, &i, chr_class);
		return (get_next_token(s, stack));
	}
	if (!(toktype = get_tok_type[chr_class]))
		return (token_error(UNRECOGNIZED_TOKEN, stack, s[i]));
	token = get_token(s, &i, chr_class, stack);
	if (!is_int_empty(stack))
		return (token_error(0, stack, 0));
	if (token.tok == TOK_WORD && (s[i] == '>' || s[i] == '<') && (ft_isdigits(token.data)))
		token.tok = TOK_IO_NUMBER;
	//if (token.tok == TOK_WORD)
		//field_splitting, don't forget to use IFS who's used to determine the character to do splitting
	//printf("{%s, \"%s\"}\n", DEBUG_TOKEN[token.tok], token.data);
	if (ABSTRACT_TOKEN[token.tok] && !(token.tok = get_true_toktype(token.data, token.tok, &i)))
	{
		error_push(stack, UNRECOGNIZED_TOKEN, token.data);
		return (token_error(0, stack, 0));
	}
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
