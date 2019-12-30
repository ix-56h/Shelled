/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:28:07 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/30 19:02:12 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>

char	**init_env(char **env)
{
	struct passwd	*pw;
	char			*tmp;
	char			cwd[PATH_MAX];

	pw = getpwuid(getuid());
	if ((tmp = pw->pw_dir) && !(*getcwd(cwd, sizeof(cwd))))
		exit(EXIT_FAILURE);
	if (!(env = malloc(sizeof(char *) * 5)))
		exit(EXIT_FAILURE);
	if (!(env[0] = ft_strdup("SHLVL=0")))
		exit(EXIT_FAILURE);
	if (!(env[1] = ft_strdup("_=/usr/bin/env")))
		exit(EXIT_FAILURE);
	if (!(env[2] = ft_strdup("PWD=")))
		exit(EXIT_FAILURE);
	if (!(env[2] = ft_strjoinf(env[2], cwd, 1)))
		exit(EXIT_FAILURE);
	if (!(env[3] = ft_strdup("HOME=")))
		exit(EXIT_FAILURE);
	if (!(env[3] = ft_strjoinf(env[3], tmp, 1)))
		exit(EXIT_FAILURE);
	env[4] = 0;
	return (env);
}
