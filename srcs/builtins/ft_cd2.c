/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 01:22:07 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/07 20:18:44 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "builtins.h"

char		*set_old_path(char ***tenv)
{
	char	*path;

	if (!(path = malloc(FT_PATH_MAX + 1)))
		return (NULL);
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

int			set_new_path(char ***tenv, char *newpath)
{
	char	*path;

	if (chdir(newpath) == 0)
	{
		path = ft_calloc(FT_PATH_MAX + 1);
		getcwd(path, FT_PATH_MAX);
		ft_edit_env(*tenv, "PWD", path);
		path = ft_free(path);
		return (1);
	}
	else
		return (0);
}

int			change_path(char *new_path, char **oldpath, char ***tenv)
{
	if (!new_path && !*oldpath)
		return (ERR_CD_OLDPWD);
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
