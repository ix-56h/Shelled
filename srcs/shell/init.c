/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:49:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/08 15:52:51 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh.h"
#include "ligne.h"
#include "libft.h"

static void	add_shlvl(char ***env)
{
	char	*shlvl;
	char	*tmp;

	if ((shlvl = get_env(*env, "SHLVL")))
	{
		tmp = ft_itoa(ft_atoi(shlvl) + 1);
		ft_edit_env(*env, "SHLVL", tmp);
		free(tmp);
	}
	else
		ft_edit_env(*env, "SHLVL", "0");
}

static void	test_fd(void)
{
	struct stat buf;

	if (fstat(0, &buf) == -1)
	{
		ft_putendl_fd("IO error", 2);
		exit(1);
	}
	if (fstat(1, &buf) == -1)
	{
		ft_putendl_fd("IO error", 2);
		exit(1);
	}
	if (fstat(2, &buf) == -1)
	{
		ft_putendl_fd("IO error", 2);
		exit(1);
	}
}

void		add_necessary_env(char ***env, size_t size)
{
	char	pwd[size];
	char	*error;

	error = getcwd(pwd, size);
	if (!error)
		add_necessary_env(env, size + size);
	*env = add_env(*env, "PWD", pwd);
}

int			init_shell(t_sh *sh, int ac, char **av, char **envp)
{
	test_fd();
	if (!(sh->stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return (0);
	if (!(sh->stack.here_docs = fifo_creator(20, sizeof(t_node*))))
		return (0);
	sh->node = NULL;
	g_env = NULL;
	if (!envp[0])
		g_env = init_env(g_env);
	else
	{
		g_env = cpy_env(envp);
		add_shlvl(&g_env);
		if (!get_env(g_env, "PWD"))
			add_necessary_env(&g_env, 256);
	}
	if (!g_env)
		return (0);
	check_args(sh, ac, av);
	init_set(av);
	init_term();
	return (1);
}

void		re_init_sh(t_sh *sh)
{
	if (!(sh->stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return ;
	if (!(sh->stack.here_docs = fifo_creator(20, sizeof(t_node*))))
		return ;
	sh->node = NULL;
}
