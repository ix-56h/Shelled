/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:47:24 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/08 23:49:17 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_RULES_H
# define FT_VISITOR_RULES_H
# include "visitor.h"
# include "tokenizer.h"

int		(*g_visit_rules[TOK_POSIX_MAX]) (t_node *node, t_io_lists io,
			t_job **job) =
{
	[TOK_NAME] = visit_cmd,
	[TOK_ASSIGNMENT_WORD] = visit_assign_word,
	[TOK_LESSAND] = visit_lessand,
	[TOK_GREATAND] = visit_greatand,
	[TOK_WORD] = visit_cmd,
	[TOK_AND_IF] = visit_and_if,
	[TOK_OR_IF] = visit_or_if,
	[TOK_AND] = visit_background,
	[TOK_PIPE] = visit_pipe,
	[TOK_DLESS] = visit_dless,
	[TOK_DGREAT] = visit_dgreat,
	[TOK_LREDI] = visit_left_redi,
	[TOK_RREDI] = visit_right_redi,
	[TOK_SEMI] = visit_semi
};

#endif
