/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:43:21 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 13:08:21 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "sh.h"

int    binaire_type(char *arg, char **path_s)
{
  int cpt;
  DIR *dir;

  cpt = -1;
  while (path_s[++cpt])
  {
    dir = opendir(path_s[cpt]);
    while ((diread = readdir(dir)) != NULL)
    {
      if (ft_strcmp(arg, diread->d_name) == 0)
      {
        ft_putstr_fd(arg, 2);
        ft_putstr_fd(" is ", 2);
        ft_putstr_fd(path_s[cpt], 2);
        ft_putchar_fd('/', 2);
        ft_putendl_fd(arg, 2);
        closedir(dir);
        return (1);
      }
    }
    closedir(dir);
  }
  return (0);
}

int    builtin_type(char *arg)
{
  if (lookforbuiltin(arg) != NULL)
  {
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(" is a 42sh builtin\n", 2);
    return (1);
  }
  return (0);
}

/*
    error not found : 0
*/

void    error_type(int error, char *arg)
{
  if (error == 0)
  {
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(" not found\n", 2);
  }
}

int     ft_type(char **args, char ***tenv)
{
  int cpt;
  int error;
  char **path_s;
  char *path;

  path = get_env(*tenv, "PATH");
  path_s = ft_strsplit(path, ':');
  if (ft_strcmp(args[1], "--") == 0)
    cpt = 1;
  else
    cpt = 0;
  while (args[++cpt])
  {
    if ((error = builtin_type(args[cpt])) == 0)
      error = binaire_type(args[cpt], path_s);
    error_type(error, args[cpt]);
  }
  cpt = -1;
  while (path_s[++cpt])
    free(path_s[cpt]);
  free(path_s);
  return (0);
}
