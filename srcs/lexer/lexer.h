/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:54:25 by niguinti          #+#    #+#             */
/*   Updated: 2019/09/30 04:08:28 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

enum	e_states{
	S_SHELL,	
	S_SQUOTES,
	S_DQUOTES,
	S_SUBSHELL
};
/*
**	Operators tokens
*/
enum	e_tokens {
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
};
typedef enum e_states	(*event_handler)(enum e_states, enum e_tokens);

enum e_states word_process(enum e_states state, enum e_tokens token) {
	printf("Hello World!\n");
	return S_WORD;
}

enum e_states double_quotes_process(enum e_states state, enum e_tokens token) {
	printf("Hello World!\n");
	return S_DQUOTES;
}

enum e_states single_quotes_process(enum e_states state, enum e_tokens token) {
	printf("Hello World!\n");
	return S_SQUOTES;
}


event_handler		transition_table[S_SUBSHELL + 1][In + 1] = {
	[S_SHELL] = { [WORD] = word_process, },
	[S_SQUOTES] = { [WORD] = single_quotes_process, },
	[S_DQUOTES] = { [WORD] = double_quotes_process, },
	[S_SUBSHELL] = { [WORD] = word_process, },
};

typedef	struct		s_token{
	char			*name;
	enum e_tokens	token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;
