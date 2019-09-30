/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 12:36:35 by niguinti          #+#    #+#             */
/*   Updated: 2019/09/16 15:06:14 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(int state, t_token *token);

int		ft_is_alpha(char c)
{
	if  ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int		ft_is_delimiter(char c)
{
	if  (c == ' ' || c == '\t' ||c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		ft_is_operator(char c)
{
	if  (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		ft_is_quote(char c)
{
	if  (c == '"' || c == 39)
		return (1);
	return (0);
}

int		ft_is_special(char c)
{
	if (c == '=')
		return (1);
	// * ? [ - = %
	return (0);
}

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	tokenize_delimiter(char c)
{
	size_t	ret;

	ret = 0;
	if (c == '|' && (ret = 1))
		printf("{'DELIMITER', '|', 'PIPE'}\n");
	else if (c == '&'  && (ret = 1))
		printf("{'DELIMITER', '&', 'AND'}\n");
	else if (c == ' ' && (ret = 1))
		printf("{'DELIMITER', '<space>', 'DELIMITER'}\n");
	else if (c == '\t'  && (ret = 1))
		printf("{'DELIMITER', '<tab>', 'DELIMITER'}\n");
	else if (c == ';'  && (ret = 1))
		printf("{'DELIMITER', ';', 'NEW_CMD'}\n");
	else if (c == '<'  && (ret = 1))
		printf("{'DELIMITER', '<', 'LEFT_REDIRECTION'}\n");
	else if (c == '>'  && (ret = 1))
		printf("{'DELIMITER', '>', 'RIGHT_REDIRECTION'}\n");
	return (ret);
}

size_t	tokenize_quotes(char *s)
{
	size_t	ret;
	char	cmp;

	ret = 1;
	cmp = *s;
	if (cmp == '"')
		printf("{'WORD', '<d_quote>', 'D_QUOTE', 'OPEN'}\n");
	else if (cmp == 39)
		printf("{'WORD', '<s_quote>', 'S_QUOTE', 'OPEN'}\n");
	while (s[ret] && s[ret] != cmp)
		ret++;
	if (s[ret] == cmp)
	{
		if (cmp == '"')
			printf("{'WORD', '<d_quote>', 'D_QUOTE', 'CLOSE'}\n");
		else if (cmp == 39)
			printf("{'WORD', '<s_quote>', 'S_QUOTE', 'CLOSE'}\n");
	}
	return (ret + 1);
}

unsigned int	find_word(char *w)
{
	size_t	ret;

	ret = 0;
	if (strcmp(w, "if") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'IF'}\n", w);
	else if (strcmp(w, "then") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'THEN'}\n", w);
	else if (strcmp(w, "else") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'ELSE'}\n", w);
	else if (strcmp(w, "elif") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'ELIF'}\n", w);
	else if (strcmp(w, "fi") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'FI'}\n", w);
	else if (strcmp(w, "do") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'DO'}\n", w);
	else if (strcmp(w, "done") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'DONE'}\n", w);
	else if (strcmp(w, "case") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'CASE'}\n", w);
	else if (strcmp(w, "esac") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'ESAC'}\n", w);
	else if (strcmp(w, "while") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'WHILE'}\n", w);
	else if (strcmp(w, "until") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'UNTIL'}\n", w);
	else if (strcmp(w, "for") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'FOR'}\n", w);
	else if (strcmp(w, "in") == 0 && (ret = 1))
		printf("{'RESERVED_WORD', '%s', 'IN'}\n", w);
	return (ret);
}

size_t	word_tokenize(char *s, t_token *tokens)
{
	size_t	ret;
	size_t	i;
	char	*tmp;

	tmp = NULL;
	ret = 0;
	i = 0;
	while (s[ret] && ((s[ret] >= 'a' && s[ret] <= 'z') || (s[ret] >= 'A' && s[ret] <= 'Z') || s[ret] == '_' || s[ret] == '-'))
		ret++;
	//use memncpy instead this mallocation if and while assignation
	if (!(tmp = malloc(sizeof(char) * (ret + 1))))
		exit(0);
	while (i < ret)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	if (!find_word(tmp))
		printf("{'\?\?\?', '%s'}\n", tmp);
	free(tmp);
	return (ret);
}

size_t	special_tokenize(char *s, t_token *tokens)
{
	size_t	ret;

	ret = 1;
	if (s[0] && s[0] == '=' && (!s[1] || s[1] != '='))
		printf("{'ASSIGNATION', '='}\n");
	if (s[0] && s[0] == '=' && (s[1] && s[1] == '=') && ret++)
		printf("{'COMPARAISON', '=='}\n");
	return (ret);
}

size_t	comment_ignore(char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret] && s[ret] != '\n')
		ret++;
	printf("{'COMMENT', '#', %zu} <- ignored\n", ret);
	return (ret);
}

size_t	integer_tokenize(char *s, t_token *tokens)
{
	size_t	ret;
	size_t	i;
	char	*tmp;

	ret = 0;
	tmp = NULL;
	i = 0;
	while (s[ret] && ft_is_digit(s[ret]))
		ret++;
	if (!(tmp = malloc(sizeof(char) * (ret + 1))))
		exit(0);
	while (i < ret)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	printf("{'INTEGER', '%s'}\n", tmp);
	free(tmp);
	return (ret);
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
	return (ret);
}

size_t	subshell_tokenize(char *s)
{
	size_t	ret;
	size_t	i;
	char	*tmp;

	tmp = NULL;
	ret = 0;
	i = 0;
	while (s[i] && s[i] != ')')
	{
		i++;
	printf("%zu\n", i);
	}
	tmp = strndup(tmp, i);
	printf("tmp = %s\n", tmp);
	free(tmp);
	return (i);
}

size_t	tokenize_backslash(char *s)
{
	size_t	ret;

	ret = 1;

	return (ret);
}

size_t  tokenize_expansion(char *s)
{
    size_t  ret;
    char    end;
    char    *tmp;
    
    ret = 0;
    end = '}';
    while (s[ret] && s[ret] != end)
      ret++;
    ret += 1;
    tmp = strndup(s, ret);
	printf("{'EXPANSION', '%s'}\n", tmp);
    free(tmp);
    return (ret);
}

size_t  tokenize_substitution(char *s)
{
    size_t  ret;
    char    end;
    char    *tmp;
    
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

size_t  tokenize_arithmetic(char *s)
{
    size_t  ret;
    char    end;
    char    *tmp;

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

t_token	*get_token(t_token *tokens, char *cmd)
{
	size_t			i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && ft_is_alpha(cmd[i]))
			i += word_tokenize(cmd + i, tokens);
		if (cmd[i] && ft_is_operator(cmd[i]))
			i += tokenize_operator(cmd + i);
		if (cmd[i] && (cmd[i] == 39 || cmd[i] == '"'))
			i += tokenize_quotes(cmd + i);
		if (cmd[i] && cmd[i] == '\\')
			i+= tokenize_backslash(cmd + i);
		if (cmd[i] && (strncmp(cmd + i, "$((", 3) == 0))
            i+= tokenize_arithmetic(cmd + i);
		if (cmd[i] && ((cmd[i] == '$' && (cmd[i + 1] && cmd[i + 1] == '(')) || cmd[i] == '`'))
            i+= tokenize_substitution(cmd + i);
		if (cmd[i] && cmd[i] == '$' && (cmd[i + 1] && cmd[i + 1] == '{'))
            i+= tokenize_expansion(cmd + i);
        if (cmd[i] && ft_is_delimiter(cmd[i]))
			i += tokenize_delimiter(cmd[i]);
		if (cmd[i] && cmd[i] == '\n') //ignore the \n for the test, need to really be process btw
			i++;
		if (cmd[i] && cmd[i] == '(')
			i+= subshell_tokenize(cmd + i);
		if (cmd[i] && cmd[i] == '#')
			i+= comment_ignore(cmd + i);
		if (cmd[i] && ft_is_special(cmd[i]))
			i += special_tokenize(cmd + i, tokens);
		if (cmd[i] && ft_is_digit(cmd[i]))
			i += integer_tokenize(cmd + i, tokens);
	}
	return (tokens);
}

t_token	*ft_tokenizer(t_token *tokens, char *cmd)
{
	t_token *first = tokens;

	get_token(tokens, cmd);
	return (first);
}

int		main(int ac, char **av)
{
	t_token *tokens = NULL;

	if (ac != 2)
		return (EXIT_FAILURE);
	tokens = ft_tokenizer(tokens, av[1]);
	return (EXIT_SUCCESS);
}
