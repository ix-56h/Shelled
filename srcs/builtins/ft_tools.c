/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"

int		f_type(char **path_s)
{
	int cpt;

	cpt = -1;
	if (!path_s)
		return (0);
	while (path_s[++cpt])
		free(path_s[cpt]);
	free(path_s);
	return (0);
}

int		ft_len(char **args)
{
	int cpt;

	cpt = 0;
	while (args[cpt])
		cpt++;
	return (cpt);
}

void	h_env(char ***tenv)
{
	char *home;
	char *pwd;
	char *old_pwd;

	if (!(pwd = get_env(*tenv, "PWD")))
	{
		add_necessary_env(tenv, 256);
		pwd = get_env(*tenv, "PWD");
	}
	old_pwd = get_env(*tenv, "OLDPWD");
	if (!(home = get_env(*tenv, "HOME")))
		home = getpwuid(getuid())->pw_dir;
	update_env(tenv, pwd, old_pwd, home);
}

int		ft_str_free(char *s1, char *s2)
{
	int ret;
	int cpt;

	cpt = 0;
	while (s1[cpt] && s2[cpt])
	{
		if (s1[cpt] != s2[cpt])
			return (s1[cpt] - s2[cpt]);
		cpt++;
	}
	ret = s1[cpt] - s2[cpt];
	if (ret == 0)
		free(s1);
	return (ret);
}
