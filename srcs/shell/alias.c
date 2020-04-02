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

char *alloc_check(char *input, int cpt)
{
  int alloc;
  char *alias;

  alloc = 0;
  while (input[cpt] != ' ' && input[cpt])
  {
    alloc += 1;
    cpt += 1;
  }
  if (!(alias = (char*)malloc(sizeof(char) * (alloc + 1))))
    return (NULL);
  cpt -= alloc;
  alloc = 0;
  while (input[cpt] && input[cpt] != ' ')
  {
    alias[alloc] = input[cpt];
    alloc++;
    cpt += 1;
  }
  alias[alloc] = '\0';
  return (alias);
}

char      *check_alias(char *input, int *cpt)
{
  char *alias;

  if (!(alias = alloc_check(input, *cpt)))
    return (input);
  input = print_alias(alias, input, *cpt);
  *cpt += ft_strlen(alias);
  while (input[*cpt] == ' ' && input[*cpt])
    *cpt += 1;
  *cpt -= 1;
  free(alias);
  return (input);
}

int  ignore_quotes(char *input, int c, int cpt)
{
  cpt++;
  while (input[cpt] != c && input[cpt])
    cpt++;
  cpt++;
  return (cpt);
}

char *add_alias(char *input)
{
  int cpt;

  cpt = -1;
  if (!g_alias)
    return (input);
  while (input[++cpt])
  {
    if (input[cpt] == '\'' || input[cpt] == '\"')
      cpt = ignore_quotes(input, input[cpt], cpt);
    if (input[cpt] != ' ' && input[cpt])
      input = check_alias(input, &cpt);
    if (input[cpt] == '\0')
      break ;
  }
  return (input);
}
