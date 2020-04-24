/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_non_zero_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_non_zero_size(char *s1, char *s2)
{
  if (ft_strlen(s1) > 0)
  {
    ft_printf("-n | true\n");
    return (0);
  }
  (void)s2;
  ft_printf("-n | false\n");
  return (1);
}
