/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "sh.h"

static char		*change_test_path(char *arg)
{
	char *pwd;

	pwd = get_env(g_env, "PWD");
	arg = new_path(arg, pwd, 0);
	return (arg);
}

char			*apply_path(char *arg)
{
	if (ft_strlen(arg) == 0)
		return ("");
	concat_pwd(arg, '/');
	if (arg[0] == '/')
		return (arg);
	else
		arg = change_test_path(arg);
	return (arg);
}

int				init_integer(char **args, size_t p_size)
{
	size_t cpt;

	cpt = 0;
	while (args[1 + p_size][cpt] >= '0'
			&& args[1 + p_size][cpt] <= '9'
			&& args[1 + p_size][cpt])
		cpt++;
	if (cpt != ft_strlen(args[1 + p_size]))
		return (error_test(args[1 + p_size], 3));
	cpt = 0;
	while (args[3 + p_size][cpt] >= '0'
			&& args[3 + p_size][cpt] <= '9'
			&& args[3 + p_size][cpt])
		cpt++;
	if (cpt != ft_strlen(args[3 + p_size]))
		return (error_test(args[3 + p_size], 3));
	return (0);
}

int				simple_operand(char **args)
{
	if (ft_strlen(args[1]) == 0)
		return (1);
	return (0);
}

int				error_test(char *arg_err, int mod)
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
