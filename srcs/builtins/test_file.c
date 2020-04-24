/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_file(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("file | false path\n");
    return (1);
  }
  if (S_ISREG(st.st_mode))
  {
    ft_printf("file | true\n");
    return (0);
  }
  ft_printf("file | false not a file\n");
  (void)s2;
  return (1);
}
