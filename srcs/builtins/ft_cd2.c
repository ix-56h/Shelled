/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:43:46 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/07 19:37:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "ft_printf.h"

int		error_cd(int error_mod, char *path)
{
	if (error_mod == 1)
		ft_putstr_fd("42sh: cd: OLDPWD not set\n", 2);
	else if (error_mod == 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (error_mod == 3)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_mod == 4)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_mod == 5)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	return (error_mod);
}

void	rm_dir(char *s)
{
	int j;

	j = 0;
	while (s[j])
		j++;
	if (j == 1)
		return ;
	while (s[j] != '/')
		j--;
	if (j > 1)
		s[j] = '\0';
	else
		s[++j] = '\0';
}

char	*add_dir(char *pwd, char *new)
{
	pwd = ft_strjoinf(pwd, "/", 1);
	pwd = ft_strjoinf(pwd, new, 1);
	return (pwd);
}

void	concat_pwd(char *str, char c)
{
	int j;
	int i;

	i = -1;
	j = 0;
	if (!str)
		return ;
	while (str[++i])
	{
		if ((str[i] == c && str[i + 1] != c) || str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
}

char	*new_path(char *add_to_path, char *pwd, int flags)
{
	char	**arg;
	char	*save;
	int		i;

	save = ft_strdup(pwd);
	i = -1;
	arg = ft_strsplit(add_to_path, '/');
	while (arg[++i])
	{
		if (ft_strcmp(arg[i], "..") == 0)
			rm_dir(save);
		else
			save = add_dir(save, arg[i]);
		free(arg[i]);
	}
	free(arg);
	concat_pwd(save, '/');
	if (flags == 3 || flags == 4)
		save = ft_strjoinf("/", ft_get_link(save), 2);
	free(add_to_path);
	add_to_path = ft_strdup(save);
	free(save);
	return (add_to_path);
}
