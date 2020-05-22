/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wexp_rules.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:56 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 00:31:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEXP_RULES_H
# define WEXP_RULES_H

enum	e_wexp
{
	BQU,
	DQU,
	SQU,
	DOL
};

char	g_wexp_rules[4][255] =
{
	[DQU] = {
		['`'] = 1,
		['$'] = 1
	},
	[BQU] = {
		['\''] = 1,
		['"'] = 1,
		['$'] = 1
	},
	[DOL] = {
		['$'] = 1,
	}
};
#endif
