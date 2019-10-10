/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 lexer.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: niguinti <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/08/26 12:36:35 by niguinti		   #+#	  #+#			  */
/*	 Updated: 2019/09/16 15:06:14 by niguinti		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../includes/tokenizer.h"
#include "../includes/lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_is_alpha(char c)
{
	if	((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	tokenize_operator(char *s)
{
	size_t	ret;
	size_t	i;
	char	*tmp;

	ret = 0;
	i = 0;
	if(strncmp("<<-", s, 3) == 0 && (ret = 3))
		printf("{'OPERATOR', '<<-', DLESSDASH}\n");
	else if(strncmp("||", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '||', OR_IF}\n");
	else if(strncmp(">|", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '>|', CLOBBER}\n");
	else if(strncmp("&&", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '&&', AND_IF}\n");
	else if(strncmp(";;", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', ';;', DSIME}\n");
	else if(strncmp("<<", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '<<', DLESS}\n");
	else if(strncmp(">>", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '>>', DGREAT}\n");
	else if(strncmp("<&", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '<&', LESSAND}\n");
	else if(strncmp(">&", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '>&', GREATAND}\n");
	else if(strncmp("<>", s, 2) == 0 && (ret = 2))
		printf("{'OPERATOR', '<>', LESSGREAT}\n");
	else
		printf("{'SYNTAX ERROR'}\n");
	return (ret);
}

size_t	tokenize_substitution(char *s)
{
	size_t	ret;
	char	end;
	char	*tmp;
	
	ret = 1;
	if (*s == '$')
		end = ')';
	else
		end = '`';
	while (s[ret] && s[ret] != end)
	  ret++; 
	ret += 1;
	tmp = strndup(s, ret);
	printf("{'SUBSTITUTION', '%s'}\n", tmp);
	free(tmp);
	return (ret);
}

size_t	tokenize_arithmetic(char *s)
{
	size_t	ret;
	char	end;
	char	*tmp;

	ret = 0;
	while (s[ret] && s[ret] != ')')
	  ret++;
	if (s[ret + 1] && s[ret + 1] == ')')
	{
		tmp = strndup(s, ret + 2);
		printf("{'ARITHMETIC', '%s'}\n", tmp);
		free(tmp);
		return (ret + 2);
	}
	else
		printf("SYNTAX ERROR\n");
	return (ret);
}

t_ast	*lex_tokens(t_tokens *tok_list)
{
	t_ast	*ast = NULL;

	return (ast);
}
