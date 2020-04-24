/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_non_zero_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_non_zero_file(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("zero size file | false path\n");
    return (1);
  }
  if (st.st_size > 0)
  {
    ft_printf("zero size file | true\n");
    return (0);
  }
  ft_printf("zero size file | false not a zero size file\n");
  (void)s2;
  return (1);
}
