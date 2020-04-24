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
#include "test_builtins.h"
#include "libft.h"
#include "ft_printf.h"

/*
**  mod = 0 : arguments > 4 -> test too many arguments
**  mod = 1 : no binary operand && arguments == 2 -> test unary expected  --> need only one arg
**  mod = 2 : no binary operand && arguments == 3 -> test binary expected
**  mod = 3 : for integer binary operand -> one of operand not an integer
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
  if (mod == 3)
  {
    ft_putstr_fd(arg_err, 2);
    ft_putstr_fd(": integer expression expected\n", 2);
  }
  return (2);
}

int  check_binary(char **args)
{
  int cpt;

  cpt = -1;
  while (g_operand[++cpt].operand != NULL)
    if (g_operand[cpt].is_unary == 0
        && !ft_strcmp(g_operand[cpt].operand, args[2]))
    {
      if (g_operand[cpt].is_pathname == 0 && init_integer(args) == 2)
        return (2);
      return (g_operand[cpt].func_op(args[1], args[3])); //for integer do atoi
    }
  return (error_test(args[2], 2));
}

int  check_unary(char **args)
{
  int cpt;

  cpt = -1;
  while (g_operand[++cpt].operand != NULL)
  {
    if (g_operand[cpt].is_unary == 1
        && !ft_strcmp(g_operand[cpt].operand, args[1]))
      {
        if (g_operand[cpt].is_pathname == 1)
          args[2] = apply_path(args[2]);
        return (g_operand[cpt].func_op(args[2], NULL));
      }
  }
  return (error_test(args[1], 1));
}

int  simple_operand(char **args)
{
  if (ft_strlen(args[1]) == 0)
  {
    ft_printf("simple | false\n");
    return (1);
  }
  ft_printf("simple | true\n");
  return (0);
}

/*
**
**  return 1 if false
**  return 0 if true
**
*/

int  ft_test(char **args, char ***env)
{
  int cpt;

  cpt = 0;
//  ft_printf("test | args 2 : %s\n", args[2]);
  while (args[cpt])
    cpt++;
  if (cpt == 4)
    return (check_binary(args));
  if (cpt == 3)
    return (check_unary(args));
  if (cpt == 2)
    return (simple_operand(args));
  if (cpt == 1)
    return (1);
  (void)env;
  return (error_test(NULL, 0));
}
