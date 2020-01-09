/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:43:46 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/09 21:56:41 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include "sh.h"
#include "libft.h"
#include "builtins.h"

static int	err_acces(char *buff, int error)
{
	if (error == ERR_PATH_ACCES)
		ft_vprint(3, "cd: permission denied: ", buff, "\n");
	else if (error == ERR_NO_FILE)
		ft_vprint(3, "cd: no such file or directory: ", buff, "\n");
	else if (error == ERR_CD_OLDPWD)
		ft_putendl("cd: no such old path");
	return (error);
}

static char			*set_old_path(char ***tenv)
{
	char	*path;

	path = malloc(FT_PATH_MAX + 1);
	path[FT_PATH_MAX] = 0;
	if (getcwd(path, FT_PATH_MAX))
	{
		ft_edit_env(*tenv, "OLDPWD", path);
		return (path);
	}
	else
	{
		path = ft_free(path);
		return (NULL);
	}
}

static int			set_new_path(char ***tenv, char *newpath)
{
	char	*path;

	if (chdir(newpath) == 0)
	{
		path = malloc(FT_PATH_MAX + 1);
		path[FT_PATH_MAX] = 0;
		getcwd(path, FT_PATH_MAX);
		ft_edit_env(*tenv, "PWD", path);
		path = ft_free(path);
		return (1);
	}
	else
		return (0);
}

static int			change_path(char *new_path, char **oldpath, char ***tenv)
{
	if (access(new_path, F_OK) == 0)
	{
		if (access(new_path, X_OK) == 0)
		{
			*oldpath = ft_free(*oldpath);
			*oldpath = set_old_path(tenv);
			if (!set_new_path(tenv, new_path))
				return (ERR_NO_FILE);
		}
		else
			return (ERR_PATH_ACCES);
	}
	else
		return (ERR_NO_FILE);
	return (0);
}

int					ft_cd(char **argv, char ***tenv)
{
	static char	*oldpath = NULL;
	char		*tmp;
	int			argc;
	int			ft_err;

	ft_err = 0;
	argc = count_arg(argv);
	if (argc == 0)
		ft_err = change_path(getenv("HOME"), &oldpath, tenv); //getenv ?
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		if ((tmp = getenv("OLDPWD"))) //getenv???
			ft_err = change_path(tmp, &oldpath, tenv);
		else
			ft_err = change_path(oldpath, &oldpath, tenv);
		if (ft_err != 0)
			ft_err = ERR_CD_OLDPWD;
	}
	else
		ft_err = change_path(argv[1], &oldpath, tenv);
	if (ft_err != 0)
		return (err_acces(argv[1], ft_err));
	return (0);
}
