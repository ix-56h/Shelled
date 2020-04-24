/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fifo.c                                        :+:      :+:    :+:   */
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

int test_fifo(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("fifo | flase not a path\n");
    return (1);
  }
  if (S_ISFIFO(st.st_mode))
  {
    ft_printf("fifo | true\n");
    return (0);
  }
  ft_printf("fifo | false fifo\n");
  (void)s2;
  return (1);
}
