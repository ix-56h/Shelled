/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:54:25 by niguinti          #+#    #+#             */
/*   Updated: 2019/10/01 05:33:20 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef enum	e_shellstates{
	S_DEFAULT,
	S_PIPE,
	S_REDIRECTION,
	S_DQUOTES,
	S_SQUOTES
} t_shellstates;

/*
**	Operators tokens
*/
typedef enum	e_tokens {
	WORD, ASSIGNEMENT_NAME, NAME, NEWLINE, IO_NUMBER,
	AND_IF, OR_IF, DSEMI,
	DLESS, DGREAT, LESSAND, GREATAND, LESSGREAT, DLESSDASH,
	CLOBBER,
	/*
	**	Reserved words tokens
	*/
	If, Then, Else, Elif, Fi, Do, Done,
	Case, Esac, While, Until, For,
	/*
	**	These are reserved words, not operator tokens, and are
	**	recognized when reserved words are recognized.
	*/
	Lbracet, Rbracet, Bang,
	In
} t_tokens;

t_shellstates	states[S_SUBSHELL + 1][In + 1] = {
	[S_DEFAULT] = { [WORD] = word_process, },
	[S_PIPE] = { [WORD] = pipe_process, },
	[S_REDIRECTIONS] = { [WORD] = redirection_process, },
	[S_DQUOTES] = { [WORD] = double_quotes_process, },
	[S_SQUOTES] = { [WORD] = single_quotes_process, },
};

typedef	struct		s_token{
	char			*name;
	enum e_tokens	token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;
