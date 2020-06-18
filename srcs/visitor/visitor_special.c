/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:35:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/12 19:05:07 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "visitor.h"
#include "ligne.h"
#include "exec.h"
#include "builtins.h"
#include "ft_printf.h"

int		visit_and_if(t_node *node, t_io_lists io, t_job **job)
{
	int			err;
	t_process	*process;

	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->state == 3)
		grp_cmd_wrapper(&io);
	err = (*g_visit_rules[node->left->tok])(node->left, io, job);
	process = (t_process *)dl_get_last((t_dl_node *)(*job)->list);
	if (process && process->pid != ERR_JOB && process->ret == 0
	&& node->left->tok != TOK_ASSIGNMENT_WORD)
	{
		if (err == 0)
			err = (*g_visit_rules[node->right->tok])(node->right, io, job);
	}
	else if (node->left->tok == TOK_ASSIGNMENT_WORD)
		err = (*g_visit_rules[node->right->tok])(node->right, io, job);
	if (node->state == 3)
		dl_del_one_with_data(io.grp_io, free);
	return (err);
}

int		visit_or_if(t_node *node, t_io_lists io, t_job **job)
{
	t_process	*process;
	int			err;

	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->state == 3)
		grp_cmd_wrapper(&io);
	err = (*g_visit_rules[node->left->tok])(node->left, io, job);
	process = (t_process *)dl_get_last((t_dl_node *)(*job)->list);
	if ((process && (process->pid == ERR_JOB || process->ret != 0 || err != 0))
			|| (!process && node->left->tok != TOK_ASSIGNMENT_WORD))
		err = (*g_visit_rules[node->right->tok])(node->right, io, job);
	else if (process && err == 0 && process->ret == 0)
		err = 0;
	if (node->state == 3)
		dl_del_one_with_data(io.grp_io, free);
	return (err);
}

int		visit_exec_pipe(t_node *node, t_io_lists io, t_job **job, int *pipefd)
{
	int		ret;

	if (pipe(pipefd) == -1)
		return (1);
	dl_push_node((t_dl_node **)&io.piped, ft_calloc(sizeof(t_pipe_list)));
	io.piped->fd[0] = pipefd[0];
	io.piped->fd[1] = pipefd[1];
	if (node->left->tok == TOK_ASSIGNMENT_WORD)
		visit_assign_pipe(node, &io, job, pipefd);
	else if ((ret = ((*g_visit_rules[node->left->tok])(node->left, io, job))))
	{
		close(pipefd[WRITE_END]);
		set_used_fd(io.piped);
	}
	ret = (*g_visit_rules[node->right->tok])(node->right, io, job);
	if (node->left->tok == TOK_ASSIGNMENT_WORD)
		restore_env_back(node->left);
	dl_del_one((t_dl_node *)io.piped);
	return (ret);
}

int		visit_pipe(t_node *node, t_io_lists io, t_job **job)
{
	int		pipefd[2];
	int		ret;

	ret = 1;
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	if (node->left && node->right)
	{
		if (node->state == 3)
			grp_cmd_wrapper(&io);
		ret = visit_exec_pipe(node, io, job, pipefd);
		if (node->state == 3)
			dl_del_one_with_data(io.grp_io, free);
	}
	return (ret);
}

int		visit_semi(t_node *node, t_io_lists io, t_job **job)
{
	int				ret;
	char			*tmp;

	if (node->state == 3)
		grp_cmd_wrapper(&io);
	if (node->state == 2)
		return (subshell_wrapper(node, &io, job));
	ret = visit(node->left, io.cmd, io.grp_io);
	if ((tmp = cut_command(io.cmd, 1)))
		free(tmp);
	ret += visit(node->right, io.cmd, io.grp_io);
	if (node->state == 3)
		dl_del_one_with_data(io.grp_io, free);
	return (ret);
}
