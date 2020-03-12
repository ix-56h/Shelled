/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:50:16 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/12 04:14:47 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOB_H
# define FT_JOB_H
# include <sys/types.h>
# include "double_linked_list.h"

# define UNUSED_JOB		-10
# define BUILTIN_JOB	-2
# define ERR_JOB		-20

typedef	struct			s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	char				**command;
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
	int					number;
	char                is_notified;
	char                *line;
}						t_job;

t_job					*g_job_head;

t_process	*create_process(pid_t pid);
t_process	*find_process_by_pid(t_process *process, pid_t pid);
int			job_is_finish(t_job *job);
void		clean_job(void);
void		free_all_job(t_job *job);
int			mark_process_status(pid_t pid, int status);
int			job_is_stopped(t_job *j);
int			job_is_completed(t_job *j);
void		wait_for_job(t_job *j);
void		put_job_in_foreground(t_job *j, int cont);
t_job		*create_job(void);
int			get_next_job_count(void);
char		*cut_command(char *cmd, char act);
#endif