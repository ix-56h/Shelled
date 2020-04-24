/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"

int test_socket(char *s1, char *s2)
{
  if (stat(s1, &st) < 0)
  {
    ft_printf("socket | false path\n");
    return (1);
  }
  if (S_ISSOCK(st.st_mode))
  {
    ft_printf("socket | true\n");
    return (0);
  }
  ft_printf("socket | false not a socket\n");
  (void)s2;
  return (1);
}
