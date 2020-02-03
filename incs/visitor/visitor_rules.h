/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:47:24 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 03:46:04 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_RULES_H
# define FT_VISITOR_RULES_H
# include "visitor.h"
# include "tokenizer.h"

int		(*g_visit_rules[TOK_POSIX_MAX]) (t_node *node\
		, t_io_lists io, int *rets) =
{
	[TOK_NAME] = visit_cmd,
	[TOK_ASSIGNMENT_WORD] = NULL,
	[TOK_LESSAND] = visit_lessand,
	[TOK_GREATAND] = visit_greatand,
	[TOK_LESSGREAT] = visit_lessgreat,
	[TOK_WORD] = visit_cmd,
	[TOK_AND_IF] = visit_and_if,
	[TOK_OR_IF] = visit_or_if,
	[TOK_AND] = NULL,
	[TOK_PIPE] = visit_pipe,
	[TOK_DLESS] = visit_dless,
	[TOK_DGREAT] = visit_dgreat,
	[TOK_LREDI] = visit_left_redi,
	[TOK_RREDI] = visit_right_redi,
	[TOK_SEMI] = visit_semi
};

#endif
