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

#include "builtins.h"
#include "sh.h"
#include "ft_printf.h"
#include "tokenizer.h"

char  *test_alias(char *alias_n)
{
  char *name_g;
  int cpt;

  cpt = -1;
  while (g_alias[++cpt])
  {
    name_g = get_name(g_alias[cpt]);
    if (ft_strcmp(name_g, alias_n) == 0)
    {
      free(name_g);
      free(alias_n);
      return (get_value(g_alias[cpt]));
    }
    free(name_g);
  }
  free(alias_n);
  return (NULL);
}

int  get_len(char *input, int cpt)
{
  int   its_q;
  char  w_q;
  int   i;

  i = cpt;
  w_q = 0;
  its_q = 0;
  if (input[i] == '\'' || input[i] == '\"')
  {
    w_q = input[i];
    its_q = 1;
    i++;
  }
  if (its_q == 1)
    while (input[i] && input[i] != w_q)
      i++;
  else
    while (input[i] && input[i] != ' ')
      i++;
  return (i - cpt);
}

char *get_command(char *input, int cpt)
{
  char  *alias_n;
  int   i;
  int   id;

  i = get_len(input, cpt);
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
  return (alias_n);
}

/*
char *new_input(char *alias_v, char *input, int *cpt, int len_n)
{
  char *after;
  char *before;
  char *new_input;

  after = get_after(input, *cpt + len_n);
  before = get_before(input, *cpt);
  if (cpt == 0)
    new_input = print_no_before(alias_v, after);
  else if (ft_strlen(input) == (*cpt + len_n))
    new_input = print_no_after(before, alias_v);
  else
    new_input = print_before_and_after(before, alias_v, after);
  *cpt += ft_strlen(alias_v);
  free(input);
  return (new_input);
}*/

void ignore_args_n_op(char *input, int *cpt)
{
  t_toktype op;
  char *name;
  size_t l;

  ft_printf("input : |%s|, char cpt : |%c|, cpt : %d    -> ignore 1\n", input, input[*cpt], *cpt);
  getchar();
  while (input[*cpt])
  {
    while (input[*cpt] == ' ' && input[*cpt])
      *cpt += 1;
    name = get_command(input, *cpt);
    l = ft_strlen(name);
    if ((op = check_redirections(name, l, cpt)) != 0
        || (op = check_operator(name, l, cpt)) != 0
        || (op = check_pipe(name, l, cpt)) != 0)
    {
      ft_printf("input : |%s|, char cpt : |%c|, cpt : %d    -> ignore 2\n", input, input[*cpt], *cpt);
      getchar();
      *cpt += ft_strlen(name);

      ft_printf("input : |%s|, char cpt : |%c|, cpt : %d    -> ignore 3\n", input, input[*cpt], *cpt);
      getchar();

      while (input[*cpt] == ' ' && input[*cpt])
        *cpt += 1;
      *cpt -= 1;
      ft_printf("input : |%s|, char cpt : |%c|, cpt : %d    -> ignore 4\n", input, input[*cpt], *cpt);
      getchar();

      free(name);
      return ;
    }
    *cpt += ft_strlen(name);
    free(name);
  }
}

char *add_alias(char *input)
{
  int   cpt;
  int   len_n;
  char  *alias_n;

  if (!g_alias)
    return (input);
  rm_first_space(input);
  cpt = -1;
  while (input[++cpt])
  {
    ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 1\n", input, input[cpt], cpt);
    getchar();

    alias_n = get_command(input, cpt);  //  return the word where cpt start

    ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 2\n", input, input[cpt], cpt);
    ft_printf("command : |%s|\n", alias_n);
    getchar();

    if (alias_n)
    {
      len_n = ft_strlen(alias_n);   // save len alias name for add cpt if no new_input


      if ((alias_n = test_alias(alias_n)))  // test if alias_n is an alias if its true return the value esle return NULL
      {
        ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 3\n", input, input[cpt], cpt);
        ft_printf("alias_n : |%s|\n", alias_n);
        getchar();

        input = new_input(alias_n, input, &cpt, len_n);  // modify input whith the alias value add the len to cpt

        ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 4\n", input, input[cpt], cpt);
        getchar();

      }
      else
        cpt += len_n;  // add len of word command if not aliases

      ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 5\n", input, input[cpt], cpt);
      getchar();

    }

    ft_printf("input : |%s|, char cpt : |%c|, cpt : %d     -> 6\n", input, input[cpt], cpt);
    getchar();

    ignore_args_n_op(input, &cpt);  // cpt is place to the end of command name

//    free(alias_n);

/*  if (input[cpt] == ' ' || input[cpt] == '\t' || input[cpt] == '\n')
      cpt = ignore_args_n_op(input, cpt);
    if (input[cpt] == '\'' || input[cpt] == '\"')
      cpt = ignore_quotes(input, input[cpt], cpt);
    if (input[cpt] != ' ' && input[cpt])
      input = check_alias(input, &cpt);
    if (input[cpt] == '\0')
      break ;*/
  }
  return (input);
}
