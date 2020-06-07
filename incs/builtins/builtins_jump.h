/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_jump.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2020/06/07 21:07:16 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_JUMP_H
# define BUILTINS_JUMP_H

# include "builtins.h"

typedef	struct		s_builtins
{
	char	*command;
	int		(*builtin)(char **argv, char ***tenv);
}					t_builtins;

const t_builtins g_builtins[] =
{
	{"addpath", ft_addpath},
	{"cd", ft_cd},
	{"exit", ft_exit},
	{"echo", ft_echo},
	{"setenv", ft_setenv},
	{"take", ft_take},
	{"unsetenv", ft_unsetenv},
	{"return", ft_return},
	{"set", ft_set},
	{"unset", ft_unset},
	{"export", ft_export},
	{"type", ft_type},
	{"alias", ft_alias},
	{"unalias", ft_unalias},
	{"test", ft_test},
	{"bg", ft_bg},
	{"jobs", ft_jobs},
	{"fg", ft_fg},
	{"hash", ft_hash},
	{NULL, NULL}
};

#endif
