/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/27 01:37:51 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "builtins.h"
#include "parser.h"
#include "visitor.h"
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
		while (ret_pid > 0)
		{
			ret_pid = waitpid(-1, &ret_value, WUNTRACED);
			if ((tmp_process = find_process_by_pid(job->data, ret_pid)))
			{
				tmp_process->is_finish = 1;
				tmp_process->ret = ret_value;
			}
			else if (ret_pid != -1)
				ft_dprintf(2, SHELL_NAME": error unknow wait pid: %i\n", ret_pid);
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
	dl_append_node((t_dl_node **)&(*job)->data, (t_dl_node *)create_process(UNUSED_JOB));
	err = exec_cmd(node, NULL, *io, *job);
	wait_and_ret(*io, *job);
	set_used_fd(io->piped);
	restore_term(2);
	signal(SIGINT, SIG_DFL);
	return (err);	
}