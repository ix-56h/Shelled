/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/03/06 16:57:50 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "visitor_misc.h"
#include "ligne.h"
#include "exec.h"
#include "ft_printf.h"

static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}

void			wait_and_ret(t_io_lists io, t_job *job)
{
	int			ret_value;
	int			ret_pid;
	t_process	*tmp_process;

	if ((io.piped && !io.piped->next && io.piped->used == 1) || !io.piped)
	{
		ret_pid = 1;
		tmp_process = (t_process *)dl_get_head((t_dl_node *)job->list);
		while (tmp_process)
		{
			if (tmp_process->pid > 0)
			{
				ret_pid = waitpid(tmp_process->pid, &ret_value, WUNTRACED);
				if (!WIFSTOPPED(ret_value))
					tmp_process->is_finish = 1;
				else
					tmp_process->is_stopped = 1;
				tmp_process->ret = ret_value;
			}
			tmp_process = tmp_process->next;
		}
	}
}

int	exec_command(t_node *node, t_io_lists *io, t_job **job)
{
	int	ctrlc;
	int	err;

	ctrlc = 0;
	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	dl_append_node((t_dl_node **)&(*job)->list, (t_dl_node *)create_process(UNUSED_JOB));
	err = exec_cmd(node, NULL, *io, *job);
	wait_and_ret(*io, *job);
	set_used_fd(io->piped);
	restore_term(2);
	signal(SIGINT, SIG_DFL);
	return (err);	
}