/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_jump.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_JUMP
# define BUILTINS_JUMP

#include "builtins.h"

typedef struct t_builtins
{
  char *command;
  int (*builtin)(char **argv, char ***tenv);
} s_builtins;

const s_builtins g_builtins[] =
{
  {"addpath", ft_addpath},
  {"cd", ft_cd},
  {"exit", ft_exit},
  {"echo", ft_echo},
  {"setenv", ft_setenv},
  {"take", ft_take},
  {"unsetenv", ft_unsetenv},
  {"djob", ft_debug_job},
  {"return", ft_return},
  {"set", ft_set},
  {"unset", ft_unset},
  {"type", ft_type},
  {"alias", ft_alias},
  {"unalias", ft_unalias},
  {"test", ft_test},
  {NULL, NULL}
};

#endif
