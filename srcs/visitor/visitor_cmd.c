/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/05/11 13:01:40 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "visitor_misc.h"
#include "ligne.h"
#include "exec.h"
#include "ft_printf.h"
#include "job.h"

static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}

int	exec_command(t_node *node, t_io_lists *io, t_job **job)
{
	int	err;

	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	add_jobnb((*job)->number);
	dl_append_node((t_dl_node **)&(*job)->list, (t_dl_node *)create_process(UNUSED_JOB));
	find_process_by_pid((*job)->list, UNUSED_JOB)->command = ft_strdup(node->data);
	err = exec_cmd(node, NULL, *io, *job);
	if ((io->piped && !io->piped->next && io->piped->used == 1) || !io->piped)
	{
		if ((*job)->list->pid != BUILTIN_JOB)
		{
			if (io->background)
				put_job_in_background(*job, 0);
			else
				put_job_in_foreground(*job, 0);
		}
		(*job)->line = cut_command(io->cmd, 0);
	}
	set_used_fd(io->piped);
	restore_term(2);
	signal(SIGINT, SIG_DFL);
	return (err);
}
