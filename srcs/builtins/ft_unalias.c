/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "libft.h"
#include "ft_printf.h"

/*
    mod = 0 : wrong usage
    mod = 1 : not found
*/

int unalias_error(int mod)
{
  if (mod == 0)
    ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]", 2);
  return (1);
}

int   ft_unalias(char **args, char ***env)
{
/*  int cpt;

  cpt = 0;
  if (ft_tablen(args) == 1)
    return (unalias_error(1));
  while (args[++cpt])
  {

  }*/
  (void)args;
  (void)env;
  return (0);
}
