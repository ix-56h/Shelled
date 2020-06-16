/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:36 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/11 18:46:43 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "stack.h"
# include "libft.h"

typedef enum		e_toktype {
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
	TOK_WORD,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_AND,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_LREDI,
	TOK_RREDI,
	TOK_BANG,
	TOK_EOF,
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
	TOK_PIPE,
	TOK_POSIX_MAX,
	TOK_RPAREN,
	TOK_LPAREN,
	TOK_RBRACE,
	TOK_LBRACE,
	TOK_ESCAPE,
	TOK_SUBSTITUTION,
	TOK_NEWLINE,
	TOK_SP,
	TOK_SUBSHELL,
	TOK_VALIDATOR,
	TOK_REDIRECTION,
	TOK_HERE,
	TOK_MAX
}					t_toktype;

typedef enum		e_chr_class {
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
}					t_chr_class;

typedef struct		s_tokens {
	t_toktype		tok;
	int				anchor;
	char			*data;
}					t_tokens;

typedef struct		s_gnt {
	t_chr_class		chr_class;
	t_toktype		toktype;
	t_tokens		token;
	int				i;
}					t_gnt;

/*
**	term_and_op_check.c
*/

t_toktype			check_pipe(char *s, size_t len, int *i);
t_toktype			check_redirections(char *s, size_t len, int *i);

/*
**	tokenizer_misc.c
*/

int					is_opening_class(t_chr_class chr_class);
t_tokens			token_error(int type, t_lifo*stack, char c);
t_tokens			save_token(char *s, int anchor, t_toktype toktype);
void				ignore_chr_class(char *s, int *i, t_chr_class chr_class);
int					is_special_char(t_chr_class chr_class\
									, t_chr_class prev_class);

/*
**	tokenizer.c
*/

t_toktype			get_true_toktype(char *s, t_toktype toktype, int *i);
int					get_token(char *s, t_gnt *gnt, t_lifo *stack);
t_tokens			get_next_token(char *s, t_lifo*stack);

/*
**	wordexp_tokenizer.c
*/

int					lex_match_squote(char *s, int *anchor, t_lifo *stack);
int					lex_match_dquote(char *s, int *anchor, t_lifo *stack);
int					lex_match_command_sub(char *s, int *anchor, t_lifo *stack);
int					lex_match_dol(char *s, int *anchor, t_lifo *stack);
int					lex_match_parameter(char *s, int *anchor, t_lifo *stack);

/*
**	lex_sequence.c
*/

int					lex_sequence(char *s, int *anchor, t_lifo *stack);

/*
**	wordexp_misc.c
*/

int					is_whitespace(char c);
void				skip_whitespaces(char *s, int *a);
int					ignore_arithmetic(char *s, int *a);
void				token_inits(int *a, t_chr_class *prev_class, t_gnt *g);

/*
**	gnt_standalone.c
*/

t_gnt				*gnt_standalone(size_t value);

/*
**	utils/is_arithmetic.c
*/

int					is_arithmetic(char *w);

#endif
