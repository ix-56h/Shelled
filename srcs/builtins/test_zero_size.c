/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_zero_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_zero_size(char *s1, char *s2)
{
  if (ft_strlen(s1) == 0)
  {
    ft_printf("-z | true\n");
    return (0);
  }
  ft_printf("-z | false\n");
  (void)s2;
  return (1);
}
