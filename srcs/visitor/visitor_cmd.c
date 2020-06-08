/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/08 22:31:57 by akeiflin         ###   ########.fr       */
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

static void		process_job_after_exec(t_io_lists *io, t_job **job)
{
	t_process	*last_process;

	if ((io->piped && !io->piped->next && io->piped->used == 1) || !io->piped)
	{
		last_process = ((t_process *)dl_get_last((t_dl_node *)(*job)->list));
		if (last_process->pid != BUILTIN_JOB)
		{
			if (io->background)
				put_job_in_background(*job, 0);
			else
				put_job_in_foreground(*job, 0);
		}
		if (!(*job)->line)
			(*job)->line = cut_command(io->cmd, 0);
	}
}

int				exec_command(t_node *node, t_io_lists *io, t_job **job)
{
	int	err;

	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	dl_append_node((t_dl_node **)&(*job)->list,
						(t_dl_node *)create_process(UNUSED_JOB));
	find_process_by_pid((*job)->list, -10)->command = ft_strdup(node->data);
	err = exec_cmd(node, NULL, *io, *job);
	process_job_after_exec(io, job);
	set_used_fd(io->piped);
	restore_term(2);
	signal(SIGINT, SIG_DFL);
	return (err);
}
