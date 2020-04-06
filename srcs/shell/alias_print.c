/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "ft_printf.h"

char *print_no_after(char *before, char *value)
{
  char *input;

  input = ft_strjoinf(before, value, 3);
  return (input);
}

char *print_before_and_after(char *before, char *value, char *after)
{
  char *input;

  input = ft_strjoinf(before, value, 3);
  input = ft_strjoinf(input, after, 3);
  return (input);
}

char *print_no_before(char *value, char *after)
{
  char *input;

  input = ft_strjoinf(value, after, 3);
  return (input);
}


char *new_input(char *alias_v, char *input, int *cpt, int len_n)
{
  char *after;
  char *before;
  char *new_input;

  ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> new_input 1\n", input, input[*cpt], *cpt);
  ft_printf("alias_v : |%s|\n", alias_v);
  getchar();

  after = get_after(input, *cpt + len_n);
  before = get_before(input, *cpt);

  ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> new_input 2\n", input, input[*cpt], *cpt);
  ft_printf("before : |%s|, after : |%s|\n", before, after);
  getchar();

  if (!after && !before)
  {
    write(1, "a", 1);
    new_input = ft_strdup(alias_v);
  }
  else if (*cpt == 0)
  {
    write(1, "b", 1);
    new_input = print_no_before(alias_v, after);
  }
  else if (ft_strlen(input) == (size_t)(*cpt + len_n))
  {
    write(1, "c", 1);
    new_input = print_no_after(before, alias_v);
  }
  else
  {
    write(1, "d", 1);
    new_input = print_before_and_after(before, alias_v, after);
  }
  *cpt += ft_strlen(alias_v);
  free(input);
  return (new_input);
}

/*
char    *print_alias(char *alias, char *input, int cpt)
{
  char *before;
  char *after;
  char *value;

  if (!(value = get_value_by_name(alias)))
    return (input);
  else
  {
    if (cpt == 0)
    {
      after = get_after(input, cpt + ft_strlen(alias));
      input = print_no_before (value, after);
    }
    else
    {
      before = get_before(input, cpt);
      if (input[cpt + ft_strlen(alias)] == '\0')
          return (print_no_after(before, value));
      else
        after = get_after(input, cpt);
      input = print_before_and_after(before, value, after);
    }
  }
  return (input);
}
*/
void rm_first_space(char *input)
{
  int cpt;
  int id;

  cpt = 0;
  id = 0;
  while (input[cpt] == ' ' || input[cpt] == '\t' || input[cpt] == '\n')
    cpt++;
  if (cpt == 0)
    return ;
  while (input[cpt])
  {
    input[id] = input[cpt];
    id++;
    cpt++;
  }
  input[id] = '\0';
}
