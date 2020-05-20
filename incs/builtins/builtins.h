/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/11 13:35:01 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define ERR_IS_FOLDER			1
# define ERR_PATH_ACCES			2
# define ERR_NO_FILE			3
# define ERR_CMD_NOT_FOUND		4
# define ERR_CD_OLDPWD			5
# define ERR_CD_NOT_HOME		6
# define ERR_REDIR				7

typedef int	(*t_builtin)(char **, char ***);

int			count_arg(char **argv);
void		add_bang(char *value);
int			ft_addpath(char **argv, char ***env);
int			ft_cd(char **argv, char ***tenv);
int			ft_exit(char **argv, char ***tenv);
int			ft_echo(char **argv, char ***tenv);
int			ft_setenv(char **argv, char ***env);
int			ft_take(char **argv, char ***env);
int			ft_unsetenv(char **argv, char ***env);
int			ft_debug_job(char **argv, char ***tenv);
int			ft_return(char **argv, char ***tenv);
int			ft_set(char **argv, char ***set);
int			ft_unset(char **argv, char ***set);
int			ft_export(char **agrv, char ***env);
t_builtin	lookforbuiltin(char *data);
int			change_path(char *new_path, char **oldpath, char ***tenv);
int			set_new_path(char ***tenv, char *newpath);
char		*set_old_path(char ***tenv);
int			ft_bg(char **argv, char ***tenv);
int			ft_jobs(char **argv, char ***tenv);
int			ft_fg(char **argv, char ***tenv);

#endif
