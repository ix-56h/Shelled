/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_block.c                                       :+:      :+:    :+:   */
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

int  test_block(char *s1, char *s2)
{
  (void)s2;
  ft_printf("block | %s\n", s1);
  if (stat(s1, &st) < 0)
  {
    ft_printf("block | flase not a path\n");
    return (1);
  }
  if (S_ISBLK(st.st_mode))
  {
    ft_printf("block | true\n");
    return (0);
  }
  ft_printf("block | flase not a block\n");
  return (1);
}
