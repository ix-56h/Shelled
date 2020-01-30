/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_and_op_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:33:36 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/30 13:01:34 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "error_handler.h"

t_toktype	check_operator(char *s, size_t len, int *i)
{
	t_toktype	ret;

	ret = 0;
	if (s[1] && !ft_strncmp(s, "&&", 2))
	{
		*i -= (len - 2);
		ret = TOK_AND_IF;
	}
	else if (s[1] && !ft_strncmp(s, ";;", 2))
	{
		*i -= (len - 2);
		ret = TOK_DSEMI;
	}
	else if (!ft_strncmp(s, ";", 1))
	{
		*i -= (len - 1);
		ret = TOK_SEMI;
	}
	else if (!ft_strncmp(s, "&", 1))
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

t_toktype	check_redirections(char *s, size_t len, int *i)
{
		t_toktype	ret;

		ret = 0;
		if (!ft_strcmp(s, "<<-"))
		{
			*i -= (len - 3);
			ret = TOK_DLESSDASH;
		}
		else if (!ft_strncmp(s, "<<", 2))
		{
			*i -= (len - 2);
			ret = TOK_DLESS;
		}
		else if (!ft_strncmp(s, ">>", 2))
		{
			*i -= (len - 2);
			ret = TOK_DGREAT;
		}
		else if (!ft_strncmp(s, "<&", 2))
		{
			*i -= (len - 2);
			ret = TOK_LESSAND;
		}
		else if (!ft_strncmp(s, ">&", 2))
		{
			*i -= (len - 2);
			ret = TOK_GREATAND;
		}
		else if (!ft_strncmp(s, "<>", 2))
		{
			*i -= (len - 2);
			ret = TOK_LESSGREAT;
		}
		else if (!ft_strncmp(s, ">|", 2))
		{
			*i -= (len - 2);
			ret = TOK_CLOBBER;
		}
		else if (!ft_strncmp(s, "<", 1))
		{
			*i -= (len - 1);
			ret = TOK_LREDI;
		}
		else if (!ft_strncmp(s, ">", 1))
		{
			*i -= (len - 1);
			ret = TOK_RREDI;
		}
		return (ret);
}
