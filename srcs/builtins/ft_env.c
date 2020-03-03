/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:47:22 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/02 01:05:05 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "sh.h"
#include "builtins.h"
#include "ast.h"
#include "visitor.h"
#include "exec.h"

static void	printenv(char **env)
{
	if (env)
	{
		while (*env)
		{
			ft_putendl(*env);
			++env;
		}
	}
}

static int	test_args(char ***argv)
{
	int	catch;

	catch = 0;
	while ((*++(*argv)))
	{
		if ((**argv)[0] == '-')
		{
			catch = 1;
			if (ft_strcmp(**argv, "-i") != 0)
			{
				ft_vprint(3, "env : invalid option ", **argv, "\n");
				return (-1);
			}
		}
		else
			break ;
	}
	return ((catch) ? 1 : 0);
}

static char	**set_nenv(char ***argv, char **ienv)
{
	char	*item;

	while ((*(*argv)))
	{
		if ((item = ft_strchr(**argv, '=')))
		{
			item[0] = '\0';
			if (!ienv)
				ienv = add_env(NULL, **argv, item + 1);
			else
			{
				if (!ft_edit_env(ienv, **argv, item + 1))
					ienv = add_env(ienv, **argv, item + 1);
			}
		}
		else
			break ;
		++(*argv);
	}
	if (!ienv)
	{
		ienv = ft_calloc(sizeof(char *));
		*ienv = NULL;
	}
	return (ienv);
}

static int	exec_it(char **env, char **argv)
{
	t_node		node;
	t_io_lists	io;
	int			ret;

	ret = 0;
	io = (t_io_lists) {NULL, NULL};
	node.data = *argv;
	node.args = argv;
	ret = exec_cmd(&node, env, io, NULL); //job a revoir
	if (!lookforbuiltin(*argv))
		wait(&ret);
	return (ret);
}

int			ft_env(char **argv, char ***tenv)
{
	int		test_arg_value;
	char	**n_env;
	int		ret;

	ret = 0;
	if (count_arg(argv) == 0)
		printenv(*tenv);
	else
	{
		if ((test_arg_value = test_args(&argv)) == 1)
			n_env = set_nenv(&argv, NULL);
		else if (test_arg_value == 0)
			n_env = set_nenv(&argv, cpy_env(*tenv));
		if (test_arg_value != -1)
		{
			if (!*argv)
				printenv(n_env);
			else
				ret = exec_it(n_env, argv);
			free_env(n_env);
		}
	}
	return (ret);
}
