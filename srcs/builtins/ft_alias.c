/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
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

int init_alias(char **args)
{
  int cpt;
  char *n_alias;
  char *v_alias;

  cpt = 0;
  while ((n_alias = get_value(args[cpt])) == NULL && args[cpt])
  {
    if (args[cpt] == NULL)
      return (0);
    cpt++;
  }
  free(n_alias);
  if (!(g_alias = (char**)malloc(sizeof(char*) * 2)))
    return (0);
  n_alias = get_name(args[cpt]);
  v_alias = get_value(args[cpt]);
  g_alias[0] = ft_strjoinf(n_alias, "=", 1);
  g_alias[0] = ft_strjoinf(g_alias[0], v_alias, 3);
  g_alias[1] = NULL;
  return (cpt);
}

void  realloc_alias(char *arg)
{
  int  ind;
  char *name;
  char *name_g;
  char *value;

  ind = -1;
  if ((value = get_value(arg)) == NULL)
    return ;
  name = get_name(arg);
  while (g_alias[++ind])
  {
    name_g = get_name(g_alias[ind]);
    if (ft_strcmp(name, name_g) == 0)
    {
      ft_edit_env(g_alias, name, value);
      free(name_g);
      free(name);
      free(value);
      return ;
    }
    free(name_g);
  }
  g_alias = add_env(g_alias, name, value);
  free(name);
  free(value);
}

int   ft_alias(char **args, char ***env)
{
  static int i;
  int cpt;

  (void)env;
  cpt = 0;
  while (args[++cpt])
  {
    if (i == 0)
    {
      if ((cpt = init_alias(args)) == 0)
        return (0);
      i++;
    }
    else
      realloc_alias(args[cpt]);
    show_this_alias(args[cpt]);
  }
  if (cpt == 1)
    show_alias();
  sort_alias();
  return (0);
}
