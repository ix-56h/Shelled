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
typedef enum	e_toktype {
	TOK_ERROR,
	TOK_NAME,
	TOK_IO_NUMBER,
	TOK_LESSAND,
	TOK_GREATAND,
	TOK_CLOBBER,
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
	TOK_ASSIGN,
	TOK_EQUAL,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_LREDI,
	TOK_RREDI,
	TOK_ESCAPE,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_SUBSHELL,
	TOK_SUBSTITUTION,
	TOK_BANG,
	TOK_EXP,
	TOK_EOF,
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
	CHR_BANG,
	CHR_AND,
	CHR_EQUAL,
	CHR_SEMI,
	CHR_WORD,
	CHR_DIGIT,
	CHR_VALIDATOR,
	CHR_ESCAPE,
	CHR_PIPE,
	CHR_SQUOTE,
	CHR_DQUOTE,
	CHR_COMMENT,
	CHR_EXP,
	CHR_RBRACE,
	CHR_LBRACE,
	CHR_RREDI,
	CHR_LREDI,
	CHR_RSUB,
	CHR_LSUB,
	CHR_MAX
}				t_chr_class;

typedef struct		s_tokens {
	t_toktype		tok;
	char			*data;
}					t_tokens;

t_tokens	get_sequence_token(char *s, int *i, t_toktype toktype, t_chr_class origin_class);
t_tokens	get_token(char *s, int *i, t_toktype toktype, t_chr_class prev_class);
void		ignore_chr_class(char *s, int *i, t_chr_class chr_class);
int			is_opening_class(t_chr_class chr_class);
t_tokens	save_token(char *s, int anchor, t_toktype toktype);
t_tokens	get_next_token(char *s);
//void		eat(int anchor);
#endif
