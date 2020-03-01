/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:50:16 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/02 00:00:22 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOB_H
# define FT_JOB_H
# include <sys/types.h>
# include "double_linked_list.h"

# define UNUSED_JOB		-10
# define BUILTIN_JOB	-2
# define ERR_JOB		-20

typedef					t_dl_node t_job;
typedef	struct			s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	pid_t				pid;
	char				is_finish;
	int					ret;
}						t_process;
t_job					*g_job_head;

t_process	*create_process(pid_t pid);
t_process	*find_process_by_pid(t_process *process, pid_t pid);
int			job_is_finish(t_job *job);
void		clean_job(void);

#endif