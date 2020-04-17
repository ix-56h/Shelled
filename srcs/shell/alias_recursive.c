/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"
#include "ft_printf.h"

char  *test_alias_r(char *name, char **alias_cpy, int *to_del)
{
  char	*name_g;
  char  *alias_v;
  int		cpt;

  cpt = -1;
  if (!alias_cpy)
    return (NULL);
  cpt = -1;
  while (alias_cpy[++cpt])
  {
    name_g = get_name(alias_cpy[cpt]);
    if (ft_strcmp(name_g, name) == 0)
    {
      alias_v = get_value(alias_cpy[cpt]);
      *to_del = cpt;
      free(name_g);
      free(name);
      return (alias_v);
    }
    free(name_g);
  }
  free(name);
  return (NULL);
}

char *get_command_rec(char *input, int cpt)
{
	char	*alias_n;
	int		i;
	int		id;

	i = get_len(input, cpt);
//  ft_printf("rec get_len : %d\n", i);
	if (!(alias_n = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	id = 0;
	while (id < i)
	{
		alias_n[id] = input[cpt];
		cpt++;
		id++;
	}
	alias_n[id] = '\0';
//  ft_printf("rec alias_n : %s\n", alias_n);
	return (alias_n);
}

char  *recursive_alias(char *alias_v, char **alias_cpy)
{
  char  *input_s;
  char  *name;
  int   cpt;
  int   len_n;
  int   to_del;

  cpt = -1;
  if (!alias_cpy)
    return (alias_v);
  rm_first_space(alias_v);
  input_s = ft_strdup(alias_v);
  while (alias_v[++cpt])
  {
//    ft_printf("cpt rec : %d\n", cpt);
//    ft_printf("alias_v : %s\n", alias_v);
    name = get_next_word(alias_v, cpt);
//    ft_printf("name : %s\n", name);
//    getchar();
    if (name)
    {
      len_n = ft_strlen(name);
//      new_cpt = -1;
//      while (alias_cpy[++new_cpt])
//        ft_printf("cpy : %s\n", alias_cpy[cpt]);
      if ((name = test_alias_r(name, alias_cpy, &to_del)))
      {
        alias_cpy = del_var(alias_cpy, get_name(alias_cpy[to_del]));
//        ft_printf("test is not the problem : %s\n", name);
//        getchar();
        alias_v = new_input(name, alias_v, &cpt, len_n);
      }
      else
      {
//        ft_printf("here is the good way\n");
        cpt += len_n;
      }
      free(name);
    }
    else
      return (alias_v);
    ignore_args_n_op(alias_v, &cpt);
  }
//  ft_printf("before rec alias_v : %s\n", alias_v);
//  ft_printf("before rec save : %s\n", input_s);
//  getchar();
  if (alias_cpy && ft_strcmp(alias_v, input_s) != 0)
    alias_v = recursive_alias(alias_v, alias_cpy);
  return (alias_v);
}
