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

t_toktype	check_pipe(char *s, size_t len, int *i)
{
	t_toktype	ret;

	ret = 0;
	if (!ft_strncmp(s, "||", 2))
	{
		*i -= (len - 2);
		ret = TOK_OR_IF;
	}
	else if (!ft_strncmp(s, "|", 1))
	{
		*i -= (len - 1);
		ret = TOK_PIPE;
	}
	return (ret);
}

t_toktype	check_redirections_last_chance(char *s, size_t len, int *i)
{
	if (!ft_strncmp(s, ">", 1))
	{
		*i -= (len - 1);
		return (TOK_RREDI);
	}
	return (0);
}

t_toktype	check_redirections_suit(char *s, size_t len, int *i)
{
	if (!ft_strncmp(s, ">&", 2))
	{
		*i -= (len - 2);
		return (TOK_GREATAND);
	}
	else if (!ft_strncmp(s, "<>", 2))
	{
		*i -= (len - 2);
		return (TOK_LESSGREAT);
	}
	else if (!ft_strncmp(s, ">|", 2))
	{
		*i -= (len - 2);
		return (TOK_CLOBBER);
	}
	else if (!ft_strncmp(s, "<", 1))
	{
		*i -= (len - 1);
		return (TOK_LREDI);
	}
	return (check_redirections_last_chance(s, len, i));
}

t_toktype	check_redirections(char *s, size_t len, int *i)
{
	if (!ft_strcmp(s, "<<-"))
	{
		*i -= (len - 3);
		return (TOK_DLESSDASH);
	}
	else if (!ft_strncmp(s, "<<", 2))
	{
		*i -= (len - 2);
		return (TOK_DLESS);
	}
	else if (!ft_strncmp(s, ">>", 2))
	{
		*i -= (len - 2);
		return (TOK_DGREAT);
	}
	else if (!ft_strncmp(s, "<&", 2))
	{
		*i -= (len - 2);
		return (TOK_LESSAND);
	}
	return (check_redirections_suit(s, len, i));
}
