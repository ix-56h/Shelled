/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 12:19:58 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/02 11:18:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/utsname.h>

static void		sort_set(void)
{
	int		i;
	int		k;
	size_t	size;
	char	*tmp;

	size = ft_tablen(g_set);
	i = -1;
	k = size + 1;
	tmp = NULL;
	while (--k != 0)
	{
		while (++i != (k - 1))
		{
			if (ft_strcmp(g_set[i], g_set[i + 1]) > 0)
			{
				tmp = ft_strdup(g_set[i]);
				ft_strdel(&g_set[i]);
				g_set[i] = ft_strdup(g_set[i + 1]);
				ft_strdel(&g_set[i + 1]);
				g_set[i + 1] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		i = -1;
	}
}

static void		add_info_params(char **av)
{
	int		i;
	char	*tmp;
	char	*asterisk;

	i = -1;
	tmp = NULL;
	asterisk = NULL;
	while (av[++i])
	{
		tmp = ft_itoa(i);
		add_set(tmp, av[i]);
		ft_strdel(&tmp);
		if (asterisk)
		{
			tmp = ft_strjoin(asterisk, "\n");
			ft_strdel(&asterisk);
			asterisk = ft_strjoin(tmp, av[i]);
			ft_strdel(&tmp);
		}
		else
			asterisk = ft_strdup(av[i]);
	}
	add_set("*", asterisk);
	ft_strdel(&asterisk);
}

static void		add_info_id(void)
{
	char	*str;
	char	buff[BUFF_SIZE];

	str = NULL;
	ft_bzero(buff, BUFF_SIZE);
	if ((str = ft_itoa(getppid())))
		add_set("PPID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(getuid())))
		add_set("UID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(geteuid())))
		add_set("EUID", str);
	ft_strdel(&str);
	if ((gethostname(buff, sizeof(buff))) == 0)
		add_set("HOSTNAME", buff);
}

static void		get_sysname(void)
{
	char			*tmp;
	struct utsname	t_utsname;
	struct stat		statbuf;

	tmp = NULL;
	ft_memset(&t_utsname, 0, sizeof(struct utsname));
	ft_memset(&statbuf, 0, sizeof(struct stat));
	if ((uname(&t_utsname)) == 0)
		add_set("SYSNAME", t_utsname.sysname);
	add_set("?", "0");
	add_set("!", "0");
	add_set("@", "( )");
	add_set("*", "( )");
	add_set("#", "0");
	add_set("-", "--ast_draw");
	if ((tmp = ft_itoa(getpid())))
	{
		add_set("PID", tmp);
		add_set("$", tmp);
	}
	ft_strdel(&tmp);
}

void			init_set(char **av)
{
	char *shell_name;

	g_set = cpy_env(g_env);
	shell_name = ft_strjoin(get_env(g_env, "PWD"), "/42sh");
	add_set("SHELL", shell_name);
	add_set("IFS", " \t\n");
	add_set("IFS", " \t\n");
	add_info_params(av);
	add_info_id();
	get_sysname();
	sort_set();
	free(shell_name);
}
