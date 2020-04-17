/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
**  mod = 0 : arguments > 4 -> test too many arguments
**  mod = 1 : no binary operand && arguments == 2 -> test unary expected  --> need only one arg
**  mod = 2 : no binary operand && arguments == 3 -> test binary expected
*/

int  error_test(char *arg_err, int mod)
{
  ft_putstr_fd("42sh: test: ", 2);
  if (mod == 0)
    ft_putstr_fd("too many arguments\n", 2);
  if (mod == 1)
  {
    ft_putstr_fd(arg_err, 2);
    ft_putstr_fd(": unary operator expected\n", 2);
  }
  if (mod == 2)
  {
    ft_putstr_fd(arg_err, 2);
    ft_putstr_fd(": binary operator expected\n", 2);
  }
}

int  check_operand(char *arg)
{

}

int  ft_test(char **args, char ***env)
{
  int true_operand;
  int cpt;

  cpt = -1;
  while (args[++cpt])
    ft_printf("%s\n", args[cpt]);
  cpt = 0;
  while (args[cpt])
    cpt++;
  if (cpt >= 4)
    return (error_test(NULL, 0));
  if (cpt == 2)
    true_operand = check_operand(args[cpt]);

}
