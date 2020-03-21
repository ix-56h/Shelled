/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/06 20:11:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <sys/stat.h>
# include <dirent.h>

# define ERR_IS_FOLDER			1
# define ERR_PATH_ACCES			2
# define ERR_NO_FILE			3
# define ERR_CMD_NOT_FOUND		4
# define ERR_CD_OLDPWD			5
# define ERR_CD_NOT_HOME		6
# define ERR_REDIR				7

struct dirent	*diread;
struct stat *st;

typedef int	(*t_builtin)(char **, char ***);

int			count_arg(char **argv);
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
int     ft_type(char **args, char ***tenv);
t_builtin	lookforbuiltin(char *data);
int			change_path(char *new_path, char **oldpath, char ***tenv);
int			set_new_path(char ***tenv, char *newpath);
char		*set_old_path(char ***tenv);

int     error_cd(int error_mod, char *path);
char	  *ft_get_link(char *pathname);
int		  ft_is_dir(char *s);
char    *new_path(char *add_to_path, char *pwd, int flags);
void	  concat_pwd(char *str, char c);
int     add_old_pwd(char ***tenv, int flags, char *pwd, char *old_pwd);
int     check_dir(char *add_to_path, int flags);
void    update_env(char ***tenv, char *pwd, char *old_pwd, char *add_to_path);

#endif
