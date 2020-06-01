/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:50:16 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/01 18:27:17 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOB_H
# define FT_JOB_H
# include <sys/types.h>
# include <sys/wait.h>
# include "double_linked_list.h"
# include "signal.h"
# include <signal.h>
# include "ft_printf.h"

# define UNUSED_JOB		-10
# define BUILTIN_JOB	-2
# define ERR_JOB		-20
# ifndef WAIT_ANY
#  define WAIT_ANY		-1
# endif

typedef	struct			s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	char				*command;
	pid_t				pid;
	char				is_finish;
	char				is_stopped;
	int					ret;
	int					status;
}						t_process;

typedef	struct			s_job
{
	struct s_job		*next;
	struct s_job		*prev;
	t_process			*list;
	pid_t				pgid;
	char				is_notified;
	int					number;
	char				*line;
}						t_job;

typedef struct			s_jobnb
{
	int					number;
	struct s_jobnb		*next;
	struct s_jobnb		*prev;
}						t_jobnb;

t_job					*g_job_head;
t_jobnb					*g_jobnb;

t_process				*create_process(pid_t pid);
t_process				*find_process_by_pid(t_process *process, pid_t pid);
int						job_is_finish(t_job *job);
void					clean_job(void);
void					free_all_job(t_job *job);
int						mark_process_status(pid_t pid, int status);
int						job_is_stopped(t_job *j);
int						job_is_completed(t_job *j);
void					wait_for_job(t_job *j);
void					wait_for_job_background(t_job *job);
void					put_job_in_foreground(t_job *j, int cont);
void					put_job_in_background(t_job *job, int cont);
void					do_job_notification (void);
t_job					*create_job(void);
int						get_next_job_count(void);
char					*cut_command(char *cmd, char act);
void					free_job(t_job	*job);
t_job					*find_job_by_number(int nb);
void					update_status (void);
void					add_jobnb(int nb);
void					push_back(int nb);
void					del_jobnb(int nb);
void					continue_job (t_job *j, int foreground);
void					push_front(int nb);
void					format_job_info(t_job *j, const char *status);
void					mark_job_as_running (t_job *j);
void					set_up_signals(void);
void					set_up_sigchld(void);
void					restore_signals(void);

#endif
