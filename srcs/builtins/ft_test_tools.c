/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "sh.h"

static char *change_path(char *arg)
{
  char *pwd;

  pwd = get_env(g_env, "PWD");
  arg = new_path(arg, pwd, 0);
  return (arg);
}

char *apply_path(char *arg)
{
  if (ft_strlen(arg) == 0)
    return ("");
  concat_pwd(arg, '/');
  if (arg[0] == '/')
    return (arg);
  else
    arg = change_path(arg);
  return (arg);
}

int init_integer(char **args)
{
  size_t cpt;

  cpt = 0;
  while (args[1][cpt] >= '0' && args[1][cpt] <= '9' && args[1][cpt])
    cpt++;
  if (cpt != ft_strlen(args[1]))
    return (error_test(args[1], 3));
  cpt = 0;
  while (args[3][cpt] >= '0' && args[3][cpt] <= '9' && args[3][cpt])
    cpt++;
  if (cpt != ft_strlen(args[3]))
    return (error_test(args[3], 3));
  return (0);
}
