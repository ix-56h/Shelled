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

#ifndef TEST_BUILTINS_H
# define TEST_BUILTINS_H

typedef	struct		s_operands
{
	char	*ope;
	int		(*func_op)(char *s1, char *s2);
	int		is_unary;
	int		is_pathname;
}					t_operand;

/*
 **	test function
*/

int					test_algebraically_equal(char *s1, char *s2);
int					test_block(char *s1, char *s2);
int					test_char(char *s1, char *s2);
int					test_dir(char *s1, char *s2);
int					test_exec(char *s1, char *s2);
int					test_fifo(char *s1, char *s2);
int					test_file(char *s1, char *s2);
int					test_greater_or_equal(char *s1, char *s2);
int					test_greater(char *s1, char *s2);
int					test_groupid_flag(char *s1, char *s2);
int					test_identical(char *s1, char *s2);
int					test_less_or_equal(char *s1, char *s2);
int					test_less(char *s1, char *s2);
int					test_non_algebraically_equal(char *s1, char *s2);
int					test_non_identical(char *s1, char *s2);
int					test_non_zero_file(char *s1, char *s2);
int					test_non_zero_size(char *s1, char *s2);
int					test_only_dir(char *s1, char *s2);
int					test_read(char *s1, char *s2);
int					test_reverse(char *s1, char *s2);
int					test_socket(char *s1, char *s2);
int					test_symbolic_link(char *s1, char *s2);
int					test_userid_flag(char *s1, char *s2);
int					test_write(char *s1, char *s2);
int					test_zero_size(char *s1, char *s2);

const t_operand g_operand[] = {
	{"-b", test_block, 1, 1},
	{"-c", test_char, 1, 1},
	{"-d", test_only_dir, 1, 1},
	{"-e", test_dir, 1, 1},
	{"-f", test_file, 1, 1},
	{"-g", test_groupid_flag, 1, 1},
	{"-u", test_userid_flag, 1, 1},
	{"-L", test_symbolic_link, 1, 1},
	{"-n", test_non_zero_size, 1, 0},
	{"-s", test_non_zero_file, 1, 1},
	{"-z", test_zero_size, 1, 0},
	{"-p", test_fifo, 1, 1},
	{"-S", test_socket, 1, 1},
	{"-r", test_read, 1, 1},
	{"-w", test_write, 1, 1},
	{"-x", test_exec, 1, 1},
	{"=", test_identical, 0, 1},
	{"!=", test_non_identical, 0, 1},
	{"-eq", test_algebraically_equal, 0, 0},
	{"-ne", test_non_algebraically_equal, 0, 0},
	{"-ge", test_greater_or_equal, 0, 0},
	{"-gt", test_greater, 0, 0},
	{"-lt", test_less, 0, 0},
	{"-le", test_less_or_equal, 0, 0},
	{"n", test_reverse, 1, 0},
	{NULL, NULL, -1, -1}
};

#endif
