/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:43:46 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/07 19:37:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "sh.h"
#include "ft_printf.h"

int add_old_pwd(char ***tenv, int flags, char *pwd, char *old_pwd)
{
	if (!old_pwd)
		return (1);
	if (flags == 3 || flags == 4)
		old_pwd = ft_strjoinf("/", ft_get_link(old_pwd), 2);
	ft_edit_env(*tenv, "PWD", old_pwd);
	ft_edit_env(*tenv, "OLDPWD", pwd);
	chdir(old_pwd);
	return (0);
}

int check_dir(char *add_to_path, int flags)
{
	DIR *dir;

	if ((flags = ft_is_dir(add_to_path)) != 1)
		return (flags);
	dir = opendir(add_to_path);
	if (dir == NULL)
	{
		free(add_to_path);
		return (4);
	}
	closedir(dir);
	return (0);
}

int		ft_is_dir(char *s)
{
	struct stat st;

	if (lstat(s, &st) < 0)
	{
		free(s);
		return (3);
	}
	if (S_ISDIR(st.st_mode))
		return (1);
	if (S_ISLNK(st.st_mode))
		return (1);
	free(s);
	return (5);
}

char	*ft_get_link(char *pathname)
{
	int			nbytes;
	char		buff[255];

	nbytes = readlink(pathname, buff, sizeof(buff));
	buff[nbytes] = '\0';
	return (ft_strdup(buff));
}

void  update_env(char ***tenv, char *pwd, char *old_pwd, char *add_to_path)
{
	if (!old_pwd)
		*tenv = add_env(*tenv, "OLDPWD", pwd);
	else
		ft_edit_env(*tenv, "OLDPWD", pwd);
	ft_edit_env(*tenv, "PWD", add_to_path);
}
