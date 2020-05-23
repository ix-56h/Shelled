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
#include "ft_printf.h"
#include "libft.h"

int		step_arg(char **args, int *start)
{
	int cpt;
	int flags;

	cpt = 0;
	flags = 0;
	while (args[++cpt])
	{
		if (ft_strcmp(args[cpt], "--") == 0 || (ft_strcmp(args[cpt], "-L") != 0
					&& ft_strcmp(args[cpt], "-P") != 0))
			break ;
		if (ft_strcmp(args[cpt], "-L") == 0)
			flags += 1;
		else if (ft_strcmp(args[cpt], "-P") == 0)
			flags += 10;
	}
	*start = cpt;
	if (cpt == (int)ft_tablen(args))
		return (1);
	if (flags >= 1 && flags < 10)
		return (2);
	else if (flags >= 10)
		return (3);
	return (5);
}

int		step_to_do(char **args, char ***tenv, int *start)
{
	int		i;
	char	*path;

	i = ft_tablen(args);
	if (i == 1)
	{
		path = get_env(*tenv, "HOME");
		if (!path)
			return (0);
		return (1);
	}
	else
		return (step_arg(args, start));
}

int		form_path(char *add_to_path, char ***tenv, char flags)
{
	char *old_pwd;
	char *pwd;

	old_pwd = get_env(*tenv, "OLDPWD");
	pwd = get_env(*tenv, "PWD");
	if (ft_strcmp(add_to_path, "-") == 0)
	{
		free(add_to_path);
		return (add_old_pwd(tenv, flags, pwd, old_pwd));
	}
	if (add_to_path[0] == '/')
	{
		if (flags == 3 || flags == 4)
			add_to_path = ft_strjoinf("/", ft_get_link(add_to_path), 2);
		concat_pwd(add_to_path, '/');
	}
	else
		add_to_path = new_path(add_to_path, pwd, flags);
	if ((flags = check_dir(add_to_path, flags)) != 0)
		return (flags);
	update_env(tenv, pwd, old_pwd, add_to_path);
	chdir(add_to_path);
	free(add_to_path);
	return (0);
}

int		new_dir(char **args, char ***tenv, int flags, int start)
{
	char	*add_to_path;
	char	*save;
	int		error;

	if (ft_strcmp(args[start], "--") == 0)
		add_to_path = ft_strdup(args[++start]);
	else
		add_to_path = ft_strdup(args[start]);
	save = ft_strdup(add_to_path);
	start++;
	if (args[start])
		return (error_cd(2, add_to_path));
	error = error_cd(form_path(add_to_path, tenv, flags), save);
	free(save);
	return (error);
}

int		ft_cd(char **args, char ***tenv)
{
	int i;
	int start;

	i = step_to_do(args, tenv, &start);
	if (i == 0)
	{
		ft_printf("42sh: cd: HOME not set");
		return (-1);
	}
	else if (i == 1)
		chdir(get_env(*tenv, "HOME"));
	else
		return (new_dir(args, tenv, i, start));
	return (0);
}
