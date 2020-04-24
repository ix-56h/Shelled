/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_userid_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_userid_flag(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("-u | false pathname\n");
    return (1);
  }
  if (st.st_mode & S_ISUID)
  {
    ft_printf("-g | true\n");
    return (0);
  }
  ft_printf("-g | false no uid\n");
  (void)s2;
  return (1);
}
