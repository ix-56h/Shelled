/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 21:07:49 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/07 21:07:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <pwd.h>

# define ERR_IS_FOLDER			1
# define ERR_PATH_ACCES			2
# define ERR_NO_FILE			3
# define ERR_CMD_NOT_FOUND		4
# define ERR_CD_OLDPWD			5
# define ERR_CD_NOT_HOME		6
# define ERR_REDIR				7

typedef int	(*t_builtin)(char **, char ***);

struct dirent	*diread;
struct stat st;

int			count_arg(char **argv);
void		set_ret_value(char *var, char *value);
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
int			ft_type(char **args, char ***tenv);
int			ft_alias(char **args, char ***env);
int			ft_unalias(char **args, char ***env);
int			ft_test(char **args, char ***env);
int			ft_hash(char **argv, char ***set);

/*
** cd functions
*/

int			error_cd(int error_mod, char *path);
char		*ft_get_link(char *pathname);
int			ft_is_dir(char *s);
char		*new_path(char *add_to_path, char *pwd, int flags);
void		concat_pwd(char *str, char c);
int			add_old_pwd(char ***tenv, int flags, char *pwd, char *old_pwd);
int			check_dir(char *add_to_path, int flags);
void		update_env(char ***tenv, char *pwd, char *old_pwd, \
						char *add_to_path);
char		**get_path_or_pwd(char ***tenv);

/*
** cdpath functions
*/

char		*follow_path(char ***tenv, size_t size, char *path);
char		*follow_cd_path(char ***env, size_t size, char *path);
int			ft_str_free(char *s1, char *s2);
char		*form_algo(char *add_to_path, char *pwd, int flags);
int			un_split(char **pwd, char *add_to_path, int flags, char *save_path);

/*
** alias functions
*/

char		*get_name(char *arg);
char		*get_value(char *arg);
void		sort_alias(void);
void		show_this_alias(char *arg);
int			dispatch_show(int cpt, char ***env);
int			error_alias(char *arg, int mod);
void		free_realloc_alias(char *name_g, char *name, char *value);

/*
** test functions
*/
int			error_test(char *arg_err, int mod);
char		*apply_path(char *arg);
int			init_integer(char **args, size_t p_size);
int			simple_operand(char **args);

/*
** tools
*/

int			ft_len(char **args);
int			f_type(char **path_s);
void		h_env(char ***tenv);

#endif
