/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:46:02 by niguinti          #+#    #+#             */
/*   Updated: 2020/06/01 18:41:34 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "ligne.h"
#include "expansions.h"
#include "exec.h"
#include "visitor.h"
#include "visitor_rules.h"
#include "sh.h"
#include "parser.h"

int				exec_heredoc(t_fifo *stack)
{
	t_node	*node;
	char	*str;
	int		err;

	err = 0;
	while (!fifo_empty(stack))
	{
		node = fifo_peek(stack);
		if (node->right)
		{
			if ((str = run_heredoc(node->right->data)))
			{
				free(node->right->data);
				node->right->data = str;
				node->right->tok = TOK_HERE;
			}
			else
				err = 1;
		}
		fifo_delete(stack);
	}
	return ((err) ? 0 : 1);
}
































static void		ctrl_c_handler(int lel)
{
	(void)lel;
	ft_putchar('\n');
}

static void		child_exec_subshell_forked(t_node *node, t_io_lists io, t_job *job)
{
	pid_t	pid;
	t_job	*tmp;

	pid = getpid();
	if (!io.piped || (io.piped && !io.piped->prev && io.piped->used == 0))
	{
		setpgid(pid, pid);
		job->pgid = pid;
	}
	else
		setpgid(pid, job->pgid);
	restore_signals();
	signal(SIGINT, SIG_DFL);
	apply_fd(io);
	tmp = NULL;
	visit(node, &tmp, NULL);
	exit(15);
}

static int				exec_subshell_as_cmd(t_node *node, t_io_lists io, t_job *job)
{
	pid_t		pid;
	t_process	*process;

	if ((pid = fork()) == -1)
		return (-1);
	else if (pid == 0)
		child_exec_subshell_forked(node, io, job);
	after_fork_routine(pid, io, job);
	return (0);
}

int				exec_subshell(t_node *node, t_io_lists *io, t_job **job)
{
	int	err;

	signal(SIGINT, ctrl_c_handler);
	restore_term(1);
	add_jobnb((*job)->number);
	dl_append_node((t_dl_node **)&(*job)->list,
						(t_dl_node *)create_process(UNUSED_JOB));
	find_process_by_pid((*job)->list, -10)->command = ft_strdup(node->data);
	err = exec_subshell_as_cmd(node, *io, *job);
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

int				visit_cmd(t_node *node, t_io_lists io, t_job **job)
{
	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
	}
	else
		exec_command(node, &io, job);
	return (0);
}





int				visit_background(t_node *node, t_io_lists io, t_job **job)
{
	io.background = 1;
	if (!(*g_visit_rules[node->left->tok])(node->left, io, job))
		return (0);
	return (1);
}

int				visit(t_node *root, t_job **job, char *cmd)
{
	t_io_lists	io;
	t_job		*last_job;

	if (!root)
		return (0);
	root->data = expand_word(root->data);
	if (g_visit_rules[root->tok])
	{
		io = (t_io_lists){NULL, NULL, 0, cmd};
		last_job = create_job();
		if (!(*g_visit_rules[root->tok])(root, io, &last_job))
			return (0);
	}
	else
	{
		ft_putstr("42sh: no visit function for '");
		ft_putstr(root->data);
		ft_putstr("'\n");
	}
	return (1);
}
