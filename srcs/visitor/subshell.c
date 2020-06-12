/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:43:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/12 21:36:23 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "ligne.h"
#include "expansions.h"
#include "exec.h"
#include "visitor.h"
#include "sh.h"
#include "parser.h"

static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}

static void		child_exec_subshell_forked(t_node *node, t_io_lists io,
											t_job *job)
{
	pid_t	pid;

	pid = getpid();
	if (!io.piped || (io.piped && !io.piped->prev && io.piped->used == 0))
	{
		setpgid(pid, pid);
		job->pgid = pid;
	}
	else
		setpgid(pid, job->pgid);
	signal(SIGINT, SIG_DFL);
	apply_fd(io);
	visit(node, NULL, io.grp_io);
	exit(ft_atoi(get_env(g_set, "?")));
}

static int		exec_subshell_as_cmd(t_node *node, t_io_lists io, t_job *job)
{
	pid_t		pid;

	if ((pid = fork()) == -1)
		return (-1);
	else if (pid == 0)
		child_exec_subshell_forked(node, io, job);
	after_fork_routine(pid, io, job);
	return (0);
}

int				exec_subshell(t_node *node, t_io_lists *io, t_job **job)
{
	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	add_jobnb((*job)->number);
	dl_append_node((t_dl_node **)&(*job)->list,
						(t_dl_node *)create_process(UNUSED_JOB));
	find_process_by_pid((*job)->list, -10)->command = ft_strdup(node->data);
	exec_subshell_as_cmd(node, *io, *job);
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
	return (0);
}

int				subshell_wrapper(t_node *node, t_io_lists *io, t_job **job)
{
	node->state = -2;
	exec_subshell(node, io, job);
	return (0);
}
