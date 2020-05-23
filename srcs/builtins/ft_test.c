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

int		check_binary(char **args, int p_size)
{
	int cpt;

	cpt = -1;
	while (g_operand[++cpt].ope != NULL)
	{
		if (g_operand[cpt].is_unary == 0
				&& !ft_strcmp(g_operand[cpt].ope, args[2 + p_size]))
		{
			if (g_operand[cpt].is_pathname == 0
				&& init_integer(args, p_size) == 2)
				return (2);
			return (g_operand[cpt].func_op(args[1 + p_size], args[3 + p_size]));
		}
	}
	return (error_test(args[2 + p_size], 2));
}

int		check_unary(char **args, int p_size)
{
	int cpt;

	cpt = -1;
	while (g_operand[++cpt].ope != NULL)
	{
		if (g_operand[cpt].is_unary == 1
				&& !ft_strcmp(g_operand[cpt].ope, args[1 + p_size]))
		{
			if (g_operand[cpt].is_pathname == 1)
				args[2 + p_size] = apply_path(args[2 + p_size]);
			return (g_operand[cpt].func_op(args[2 + p_size], NULL));
		}
	}
	return (error_test(args[1 + p_size], 1));
}

int		do_reverse(char **args, int cpt)
{
	int ret;

	ret = 0;
	if (cpt == 2)
		return (0);
	if (cpt == 3)
		return (test_reverse(args[2], NULL));
	if (cpt == 4)
		ret = check_unary(args, 1);
	else if (cpt == 5)
		ret = check_binary(args, 1);
	if (ret == 0)
		return (1);
	return (0);
}

int		ft_test(char **args, char ***env)
{
	int cpt;

	cpt = 0;
	while (args[cpt])
		cpt++;
	if (cpt == 1)
		return (1);
	if (!ft_strcmp(args[1], "!"))
		return (do_reverse(args, cpt));
	if (cpt == 4)
		return (check_binary(args, 0));
	if (cpt == 3)
		return (check_unary(args, 0));
	if (cpt == 2)
		return (simple_operand(args));
	(void)env;
	return (error_test(NULL, 0));
}
