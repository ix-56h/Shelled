/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/01/12 22:08:20 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define ERR_IS_FOLDER       1
# define ERR_PATH_ACCES      2
# define ERR_NO_FILE         3
# define ERR_CMD_NOT_FOUND   4
# define ERR_CD_OLDPWD       5

int     count_arg(char **argv);
int     ft_addpath(char **argv, char ***env);
int     ft_cd(char **argv, char ***tenv);
int		ft_echo(char **argv, char ***tenv);
//int			ft_env(char **argv, char ***tenv);
int     ft_setenv(char **argv, char ***env);
int     ft_take(char **argv, char ***env);
int     ft_unsetenv(char **argv, char ***env);
#endif