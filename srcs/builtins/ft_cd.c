/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:43:46 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/07 19:37:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh.h"
#include "builtins.h"

int			err_cd(char *buff, int error)
{
	if (error == ERR_PATH_ACCES)
		ft_vprintfd(STDERR_FILENO, 3, "cd: permission denied: ", buff, "\n");
	else if (error == ERR_NO_FILE)
		ft_vprintfd(STDERR_FILENO, 3, \
					"cd: no such file or directory: ", buff, "\n");
	else if (error == ERR_CD_OLDPWD)
		ft_putendl_fd("cd: no such old path", STDERR_FILENO);
	else if (error == ERR_CD_NOT_HOME)
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
	return (error);
}

static int	no_arg(char **oldpath, char ***tenv)
{
	char	*home;

	home = get_env(g_set, "HOME");
	if (!home)
		return (err_cd(NULL, ERR_CD_NOT_HOME));
	return (err_cd(NULL, change_path(home, oldpath, tenv)));
}

static int	arg_last(char ***tenv, char **oldpath)
{
	char	*tmp;

	if ((tmp = ft_strdup(get_env(*tenv, "OLDPWD"))))
	{
		if (ft_strcmp(tmp, "") == 0)
		{
			ft_free(tmp);
			tmp = ft_strdup(*oldpath);
			if (ft_strcmp(tmp, "") == 0)
				return (err_cd(NULL, ERR_CD_OLDPWD) + (int)ft_free(tmp));
		}
		return (err_cd(tmp, change_path(tmp, oldpath, tenv)) \
						+ (int)ft_free(tmp));
	}
	else
		return (err_cd(*oldpath, change_path(*oldpath, oldpath, tenv)));
}

int			ft_cd(char **argv, char ***tenv)
{
	static char	*oldpath = NULL;
	int			argc;

	argc = count_arg(argv);
	if (argc == 0)
		no_arg(&oldpath, tenv);
	else if (ft_strcmp(argv[1], "-") == 0)
		return (arg_last(tenv, &oldpath));
	else
		return (err_cd(argv[1], change_path(argv[1], &oldpath, tenv)));
	return (0);
}
