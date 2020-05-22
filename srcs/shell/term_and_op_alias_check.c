/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_and_op_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:33:36 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 13:58:29 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "error_handler.h"

t_toktype	check_operator(char *s)
{
	t_toktype	ret;

	ret = 0;
	if (s[1] && !ft_strncmp(s, "&&", 2))
		ret = TOK_AND_IF;
	else if (s[1] && !ft_strncmp(s, ";;", 2))
		ret = TOK_DSEMI;
	else if (!ft_strncmp(s, ";", 1))
		ret = TOK_SEMI;
	else if (!ft_strncmp(s, "&", 1))
		ret = TOK_AND;
	return (ret);
}

t_toktype	check_pipe(char *s)
{
	t_toktype	ret;

	ret = 0;
	if (!ft_strncmp(s, "||", 2))
		ret = TOK_OR_IF;
	else if (!ft_strncmp(s, "|", 1))
		ret = TOK_PIPE;
	return (ret);
}

t_toktype	check_redirections_last_chance(char *s)
{
	if (!ft_strncmp(s, ">", 1))
		return (TOK_RREDI);
	return (0);
}

t_toktype	check_redirections_suit(char *s)
{
	if (!ft_strncmp(s, ">&", 2))
		return (TOK_GREATAND);
	else if (!ft_strncmp(s, "<>", 2))
		return (TOK_LESSGREAT);
	else if (!ft_strncmp(s, ">|", 2))
		return (TOK_CLOBBER);
	else if (!ft_strncmp(s, "<", 1))
		return (TOK_LREDI);
	return (check_redirections_last_chance(s));
}

t_toktype	check_redirections(char *s, size_t len, int *i)
{
	if (!ft_strcmp(s, "<<-"))
		return (TOK_DLESSDASH);
	else if (!ft_strncmp(s, "<<", 2))
		return (TOK_DLESS);
	else if (!ft_strncmp(s, ">>", 2))
		return (TOK_DGREAT);
	else if (!ft_strncmp(s, "<&", 2))
		return (TOK_LESSAND);
	return (check_redirections_suit(s, len, i));
}
