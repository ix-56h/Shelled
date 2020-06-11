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

#include "builtins.h"
#include "sh.h"

int		free_type(char **path_s)
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

void	home_env(char ***tenv)
{
	char *home;
	char *pwd;
	char *old_pwd;

	pwd = get_env(*tenv, "PWD");
	old_pwd = get_env(*tenv, "OLDPWD");
	home = get_env(*tenv, "HOME");
	update_env(tenv, pwd, old_pwd, home);
}
