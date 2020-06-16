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

#include "builtins.h"
#include "sh.h"

char	**get_path_or_pwd(char ***tenv)
{
	char **pwd;
	char *path;
	char *check_pwd;

	if (!(check_pwd = get_env(*tenv, "PWD")))
		add_necessary_env(tenv, 256);
	else
		free(check_pwd);
	path = get_env(*tenv, "CDPATH");
	if (!path)
	{
		if (!(pwd = (char**)malloc(sizeof(char*) * 2)))
			return (NULL);
		pwd[0] = get_env(*tenv, "PWD");
		pwd[1] = NULL;
	}
	else
		pwd = ft_strsplit(path, ':');
	return (pwd);
}

char		*follow_path(char ***env, size_t size, char *path)
{
	char	pwd[size];
	char	*error;
	int		cpt;

	error = getcwd(pwd, size);
	if (!error)
		add_necessary_env(env, size + size);
	cpt = ft_strlen(pwd);
	if (!ft_strcmp(path, "."))
		return (ft_strdup(pwd));
	else
	{
		while (cpt > 0 && pwd[cpt] != '/')
			cpt--;
		pwd[cpt] = '\0';
	}
	return (ft_strdup(pwd));
}


