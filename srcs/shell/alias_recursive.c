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

char  *recursive_alias(char *alias_v, char **alias_cpy, t_lifo *stack)
{
  t_tokens  token;
  char      **pot_alias;
  char      *input_s;
  int       cpt;
  int       i;
  int       to_del;

  cpt = -1;
  i = 0;
  if (!alias_cpy)
    return (alias_v);
  input_s = ft_strdup(alias_v);
  while ((token = get_next_token(alias_v, stack)).data)
  {
    ft_printf("data : %s\n", token.data);
    if (ft_strcmp(token.data, "EOF") == 0)
    {
      write(1, "\nx", 2);
      break ;
    }
    if (i == 0)
    {
      if (!(pot_alias = (char**)malloc(sizeof(char*) * 2)))
        return (NULL);
      pot_alias[0] = ft_strdup(token.data);
      pot_alias[1] = NULL;
      i++;
    }
    else
      pot_alias = add_pot(pot_alias, token.data);
  }
  free(alias_v);
  i = 0;
  cpt = -1;
  while (pot_alias[++cpt])
  {
//    ft_printf("cpt rec : %d\n", cpt);
//    ft_printf("alias_v : %s\n", alias_v);
//    ft_printf("name : %s\n", name);
//    getchar();
    if ((to_del = is_alias(pot_alias[cpt], alias_cpy)) >= 0)
    {
      if (i == 0)
        alias_v = get_value_by_name(pot_alias[cpt]);
      else
      {
        alias_v = ft_strjoin(alias_v, " ");
        alias_v = ft_strjoin(alias_v, get_value_by_name(pot_alias[cpt]));
      }
      i++;
      alias_cpy = del_var(alias_cpy, get_name(alias_cpy[to_del]));
//      new_cpt = -1;
//      while (alias_cpy[++new_cpt])
//        ft_printf("cpy : %s\n", alias_cpy[cpt]);
    }
    else
    {
      if (i == 0)
        alias_v = ft_strdup(pot_alias[cpt]);
      else
      {
        alias_v = ft_strjoin(alias_v, " ");
        alias_v = ft_strjoin(alias_v, pot_alias[cpt]);
      }
      i++;
    }
  }
//  ft_printf("before rec alias_v : %s\n", alias_v);
//  ft_printf("before rec save : %s\n", input_s);
//  getchar();
  if (alias_cpy && ft_strcmp(alias_v, input_s) != 0)
    alias_v = recursive_alias(alias_v, alias_cpy, stack);
  return (alias_v);
}
