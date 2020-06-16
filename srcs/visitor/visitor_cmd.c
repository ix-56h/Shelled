/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:12:51 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 23:34:59 by akeiflin         ###   ########.fr       */
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
#include "sh.h"
#include "builtins.h"
#include "exec.h"
#include "expansions.h"
#include "hash.h"

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
			if (need_background(io))
				put_job_in_background(*job, 0);
			else
				put_job_in_foreground(*job, 0);
		}
		if (!(*job)->line)
			(*job)->line = cut_command(io->cmd, 0);
	}
}

static int		need_fork(t_io_lists io, t_node *cmd)
{
	t_io_lists	*grp_io;
	t_dl_node	*node;
	int			grp_fork;

	grp_fork = 0;
	node = io.grp_io;
	while (node)
	{
		grp_io = node->data;
		if (grp_io->piped || grp_io->redir || grp_io->background)
		{
			grp_fork = 1;
			break ;
		}
		node = node->next;
	}
	if (!io.piped && !io.redir && !io.background && lookforbuiltin(cmd->data)
			&& !grp_fork)
		return (0);
	return (1);
}

int				exec_cmd(t_node *cmd, char **env, t_io_lists io, t_job *job)
{
	pid_t		pid;
	int			ret;
	int			i;

	i = 0;
	ret = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = expand_word(cmd->args[i]);
		i++;
	}
	if (g_exp_error)
		return (1);
	if (!need_fork(io, cmd))
		ret = exec_builtin_no_fork(cmd, env, job);
	else
	{
		if ((pid = fork()) == -1)
			return (-1);
		else if (pid == 0)
			child_exec_forked(io, g_env, job, cmd);
		add_to_table(cmd->data, 1);
		after_fork_routine(pid, io, job);
	}
	return (ret);
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
