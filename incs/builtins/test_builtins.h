/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_BUILTINS
# define TEST_BUILTINS

typedef struct s_operands
{
  char *ope;
  int  (*func_op)(char *s1, char *s2);
  int  is_unary;
  int  is_pathname;
} t_operand;

/*    test function    */

int   test_algebraically_equal(char *s1, char *s2);
int   test_block(char *s1, char *s2);
int   test_char(char *s1, char *s2);
int   test_dir(char *s1, char *s2);
int   test_exec(char *s1, char *s2);
int   test_fifo(char *s1, char *s2);
int   test_file(char *s1, char *s2);
int   test_greater_or_equal(char *s1, char *s2);
int   test_greater(char *s1, char *s2);
int   test_groupid_flag(char *s1, char *s2);
int   test_identical(char *s1, char *s2);
int   test_less_or_equal(char *s1, char *s2);
int   test_less(char *s1, char *s2);
int   test_non_algebraically_equal(char *s1, char *s2);
int   test_non_identical(char *s1, char *s2);
int   test_non_zero_file(char *s1, char *s2);
int   test_non_zero_size(char *s1, char *s2);
int   test_only_dir(char *s1, char *s2);
int   test_read(char *s1, char *s2);
int   test_reverse(char *s1, char *s2);
int   test_socket(char *s1, char *s2);
int   test_symbolic_link(char *s1, char *s2);
int   test_userid_flag(char *s1, char *s2);
int   test_write(char *s1, char *s2);
int   test_zero_size(char *s1, char *s2);

const t_operand g_operand[] = {
  {"-b",  test_block, 1, 1}, // check
  {"-c",  test_char, 1, 1}, //check
  {"-d",  test_only_dir, 1, 1}, //check
  {"-e",  test_dir, 1, 1}, //check
  {"-f",  test_file, 1, 1}, //check
  {"-g",  test_groupid_flag, 1, 1}, // check
  {"-u",  test_userid_flag, 1, 1}, // check
  {"-L",  test_symbolic_link, 1, 1}, //check
  {"-n",  test_non_zero_size, 1, 0}, //check
  {"-s",  test_non_zero_file, 1, 1}, // check
  {"-z",  test_zero_size, 1, 0},  //check
  {"-p",  test_fifo, 1, 1}, //check
  {"-S",  test_socket, 1, 1}, //check
  {"-r",  test_read, 1, 1}, // check
  {"-w",  test_write, 1, 1}, // check
  {"-x",  test_exec, 1, 1}, // check
  {"=",   test_identical, 0, 1}, // check
  {"!=",  test_non_identical, 0, 1}, // check
  {"-eq", test_algebraically_equal, 0, 0}, // integer
  {"-ne", test_non_algebraically_equal, 0, 0}, // integer
  {"-ge", test_greater_or_equal, 0, 0}, // integer
  {"-gt", test_greater, 0, 0}, // interger
  {"-lt", test_less, 0, 0}, //integer
  {"-le", test_less_or_equal, 0, 0}, // integer
  {"n",   test_reverse, 1, 0}, // expression -> to check
  {NULL, NULL, -1, -1}
};

#endif
