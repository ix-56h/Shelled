/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_non_identical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int test_non_identical(char *s1, char *s2)
{
  if (ft_strcmp(s1, s2) != 0)
  {
    ft_printf("!= | true");
    return (0);
  }
  ft_printf("!= | false");
  return (1);
}
