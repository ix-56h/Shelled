/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/06 20:11:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_operands
{
  char *operand;
  int  (*func_op)(char *s1, char *s2);
  int  binary;
} t_operand;

t_operands g_operand[] =
{
  {"-b",  test_block, 0};
  {"-c",  test_char, 0};
  {"-d",  test_dir, 0};
  {"-e",  test_only_dir, 0};
  {"-f",  test_file, 0};
  {"-g",  test_groupid_flag, 0};
  {"-u",  test_userid_flag, 0};
  {"-L",  test_symbolic_link, 0};
  {"-n",  test_non_zero_size, 0};
  {"-s",  test_non_zero_file, 0};
  {"-z",  test_zero_size, 0};
  {"-p",  test_fifo, 0};
  {"-S",  test_socket, 0};
  {"-r",  test_read, 0};
  {"-w",  test_write, 0};
  {"-x",  test_exec, 0};
  {"=",   test_identical, 1};
  {"!=",  test_non_identical, 1};
  {"-eq", test_algebraically_equal, 1}; // integer
  {"-ne", test_non_algebraically_equal, 1}; // integer
  {"-ge", test_greater_or_equal, 1}; // integer
  {"-lt", test_less, 1}; //integer
  {"-le", test_less_or_equal, 1}; // integer
  {"!",   test_reverse, 0}; // expression -> to check 
}
