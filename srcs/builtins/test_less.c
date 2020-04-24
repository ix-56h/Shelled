/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_less.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "ft_printf.h"

int test_less(char *s1, char *s2)
{
  int i1;
  int i2;

  i1 = ft_atoi(s1);
  i2 = ft_atoi(s2);
  if (i1 < i2)
  {
    ft_printf("-lt | true\n");
    return (0);
  }
  ft_printf("-lt | false\n");
  return (1);
}
