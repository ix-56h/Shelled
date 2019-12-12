/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 05:04:16 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/15 18:38:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOK_H
# define FT_TOK_H
#include "libft.h"
#include "error_handler.h"

typedef enum	e_toktype {
	TOK_ERROR,
	TOK_NAME,
	TOK_IO_NUMBER,
	TOK_ASSIGNMENT_WORD,
	TOK_LESSAND,
	TOK_GREATAND,
	TOK_LESSGREAT,
	TOK_DSEMI,
	TOK_SEMI,
	TOK_DLESSDASH,
	TOK_CLOBBER,
	TOK_IN,
	TOK_SP,
	TOK_WORD,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_AND,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_LREDI,
	TOK_RREDI,
	TOK_ESCAPE,
	TOK_SUBSHELL,
	TOK_SUBSTITUTION,
	TOK_BANG,
	TOK_RPAREN,
	TOK_LPAREN,
	TOK_NEWLINE,
	TOK_EOF,
	/*
	**	Reserved words
	*/
	TOK_IF,
	TOK_THEN,
	TOK_ELSE,
	TOK_ELIF,
	TOK_FI,
	TOK_DO,
	TOK_DONE,
	TOK_CASE,
	TOK_ESAC,
	TOK_WHILE,
	TOK_UNTIL,
	TOK_FOR,
	/*
	**	Abstract token
	*/
	TOK_VALIDATOR,
	TOK_OPERATOR,
	TOK_REDIRECTION,
	TOK_PIPE,
	TOK_MAX
}				t_toktype;

typedef enum	e_chr_class {
	CHR_ERROR,
	CHR_SP,
	CHR_DASH,
	CHR_BANG,
	CHR_AND,
	CHR_SEMI,
	CHR_WORD,
	CHR_DIGIT,
	CHR_VALIDATOR,
	CHR_ESCAPE,
	CHR_PIPE,
	CHR_SQUOTE,
	CHR_DQUOTE,
	CHR_BQUOTE,
	CHR_DOL,
	CHR_COMMENT,
	CHR_EXP,
	CHR_RBRACE,
	CHR_LBRACE,
	CHR_RREDI,
	CHR_LREDI,
	CHR_RPAREN,
	CHR_LPAREN,
	CHR_NEWLINE,
	CHR_MAX
}				t_chr_class;

typedef struct		s_tokens {
	t_toktype		tok;
	char			*data;
}					t_tokens;

t_tokens		get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class);
void			ignore_chr_class(char *s, int *i, t_chr_class chr_class);
int				is_opening_class(t_chr_class chr_class);
t_tokens		save_token(char *s, int anchor, t_toktype toktype);
t_tokens		get_next_token(char *s);
unsigned int	get_end_exp(char *s, int *i);

/*
**	wordexp_tokenizer.c
*/
int			lex_sequence(char *s, int *i, int *anchor);
int			lex_match_squote(char *s, int *i, int *anchor);
int			lex_match_dquote(char *s, int *i, int *anchor);
int			lex_match_command_sub(char *s, int *i, int *anchor);
int			lex_match_dol(char *s, int *i, int *anchor);

/*
**	wordexp_misc.c
*/
int			is_whitespace(char c);
void		skip_whitespaces(char *s,int *i,int *a);
#endif
