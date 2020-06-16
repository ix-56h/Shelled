/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:43:21 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/01 13:08:21 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "sh.h"

int		binaire_type(char *arg, char **path_s)
{
	int cpt;
	DIR *dir;

	cpt = -1;
	while (path_s[++cpt])
	{
		dir = opendir(path_s[cpt]);
		while (dir && (diread = readdir(dir)) != NULL)
		{
			if (ft_strcmp(arg, diread->d_name) == 0)
			{
				ft_putstr_fd(arg, 1);
				ft_putstr_fd(" is ", 1);
				ft_putstr_fd(path_s[cpt], 1);
				ft_putchar_fd('/', 1);
				ft_putendl_fd(arg, 1);
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
	}
	return (0);
}

int		builtin_type(char *arg)
{
	if (lookforbuiltin(arg) != NULL)
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(" is a 42sh builtin\n", 1);
		return (1);
	}
	return (0);
}

int		alias_type(char *arg)
{
	int		cpt;
	char	*value;

	if (!g_alias)
		return (0);
	cpt = -1;
	while (g_alias[++cpt])
	{
		value = get_env(g_alias, arg);
		if (value)
		{
			ft_putstr_fd(arg, 1);
			ft_putstr_fd(" is an alias for ", 1);
			ft_putendl_fd(value, 1);
			return (1);
		}
	}
	return (0);
}

void	error_type(int error, char *arg)
{
	if (error == 0)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" not found\n", 2);
	}
}

int		ft_type(char **args, char ***tenv)
{
	int		cpt;
	int		error;
	char	**path_s;
	char	*path;

	if (fcntl(1, F_GETFD) != 0 || ft_len(args) < 2)
		return (0);
	path = get_env(*tenv, "PATH");
	path_s = ft_strsplit(path, ':');
	if (ft_strcmp(args[1], "--") == 0)
		cpt = 1;
	else
		cpt = 0;
	while (args[++cpt])
	{
		if ((error = alias_type(args[cpt])) == 0)
			if ((error = builtin_type(args[cpt])) == 0 && path)
				error = binaire_type(args[cpt], path_s);
		error_type(error, args[cpt]);
	}
	return (f_type(path_s));
}
