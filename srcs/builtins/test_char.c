/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_char.c                                        :+:      :+:    :+:   */
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

int test_char(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("char | flase path\n");
    return (1);
  }
  if (S_ISCHR(st.st_mode))
  {
    ft_printf("char | true\n");
    return (0);
  }
  ft_printf("char | flase char\n");
  (void)s2;
  return (1);
}
