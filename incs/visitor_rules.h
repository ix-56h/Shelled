/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 03:47:24 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/10 17:31:22 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISITOR_RULES_H
# define FT_VISITOR_RULES_H
# include <visitor.h>
# include <tokenizer.h>

int		(*G_VISIT_RULES[TOK_POSIX_MAX]) (t_node *node) = {
	[TOK_NAME] = visit_cmd,
	//[TOK_ASSIGNMENT_WORD] = visit_assignment_word,
	[TOK_LESSAND] = visit_lessand,
	[TOK_GREATAND] = visit_greatand,
	[TOK_LESSGREAT] = visit_lessgreat,
	[TOK_WORD] = visit_cmd,
	[TOK_AND_IF] = visit_and_if,
	[TOK_OR_IF] = visit_or_if,
	//[TOK_AND] = visit_and,
	[TOK_PIPE] = visit_pipe,
	[TOK_DLESS] = visit_dless,
	[TOK_DGREAT] = visit_dgreat,
	[TOK_LREDI] = visit_left_redi,
	[TOK_RREDI] = visit_right_redi,
	[TOK_SEMI] = visit_semi
};

#endif
