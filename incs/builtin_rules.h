/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_rules.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:59:11 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 23:01:13 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_RULES_H
# define FT_BUILTIN_RULES_H
# include "builtins.h"

int		(*G_BUILTIN_RULES[6]) (t_node *node) = {
	[0] = ft_addpath,
    [1] = ft_cd,
    [2] = ft_echo,
    [3] = ft_setenv,
    [4] = ft_take,
    [5] = ft_unsetenv,
};

#endif