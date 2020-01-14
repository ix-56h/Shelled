/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/14 01:41:26 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define ERR_IS_FOLDER       1
# define ERR_PATH_ACCES      2
# define ERR_NO_FILE         3
# define ERR_CMD_NOT_FOUND   4
# define ERR_CD_OLDPWD       5
# define ERR_CD_NOT_HOME     6

typedef int	(*t_builtin)(char **, char ***);

int         count_arg(char **argv);
int         ft_addpath(char **argv, char ***env);
int         ft_cd(char **argv, char ***tenv);
int         ft_echo(char **argv, char ***tenv);
int         ft_setenv(char **argv, char ***env);
int         ft_take(char **argv, char ***env);
int         ft_unsetenv(char **argv, char ***env);
int         ft_env(char **argv, char ***tenv);

t_builtin   lookforbuiltin(char *data);

int		    change_path(char *new_path, char **oldpath, char ***tenv);
int			set_new_path(char ***tenv, char *newpath);
char		*set_old_path(char ***tenv);
#endif