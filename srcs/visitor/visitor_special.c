/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:35:24 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/02 00:20:35 by akeiflin         ###   ########.fr       */
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
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->left && node->right)
	{
		err = (*g_visit_rules[node->left->tok])(node->left, io, job);
		process = (t_process *)dl_get_last((t_dl_node *)(*job)->list);
		if (process->pid != ERR_JOB && process->ret == 0)
		{
			if (err == 0)
				if (!(*g_visit_rules[node->right->tok])(node->right, io, job))
					return (0);
		}
	}
	return (1);
}

int		visit_or_if(t_node *node, t_io_lists io, t_job **job)
{
	t_process	*process;
	int			err;

	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->left && node->right)
	{
		err = (*g_visit_rules[node->left->tok])(node->left, io, job);
		process = (t_process *)dl_get_last((t_dl_node *)(*job)->list);
		if (process->pid == ERR_JOB || process->ret != 0 || err != 0)
			if (!(*g_visit_rules[node->right->tok])(node->right, io, job))
				return (0);
		if (err == 0 && process->ret == 0)
			return (0);
	}
	return (1);
}


int		visit_pipe(t_node *node, t_io_lists io, t_job **job)
{
	int	pipefd[2];

	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	if (node->left && node->right)
	{
		if (pipe(pipefd) == -1)
			return (1);
		dl_push_node((t_dl_node **)&io.piped, ft_calloc(sizeof(t_pipe_list)));
		io.piped->fd[0] = pipefd[0];
		io.piped->fd[1] = pipefd[1];
		io.piped->used = 0;

/* *** */
	// En cas d'assignement, l'assignement s'effectue sans exécuter son node->left
	//	(visit_assign_word() n'exéxute pas si l'assignement est dans un pipe)

		if (node->left->tok == TOK_ASSIGNMENT_WORD)
		{
			if ((*g_visit_rules[node->left->tok])(node->left, io, job))
			{
				close(pipefd[WRITE_END]);
				set_used_fd(io.piped);
			}

	// Le node->left du pipe est remplacé par le node->left de l'assignement

			if ((*g_visit_rules[node->left->left->tok])(node->left->left, io, job))
			{
				close(pipefd[WRITE_END]);
				set_used_fd(io.piped);
			}
		}

/* *** */

		else if ((*g_visit_rules[node->left->tok])(node->left, io, job))
		{
			close(pipefd[WRITE_END]);
			set_used_fd(io.piped);
		}
		if (!(*g_visit_rules[node->right->tok])(node->right, io, job))
		{

// En cas d'assignement, l'environnement d'origine est restoré
			if (node->left->tok == TOK_ASSIGNMENT_WORD)
				restore_env_back(node->left);

			dl_del_one((t_dl_node *)io.piped);
			return (0);
		}
		dl_del_one((t_dl_node *)io.piped);
	}
	return (1);
}

int		visit_semi(t_node *node, t_io_lists io, t_job **job)
{
	int				ret;
	t_io_lists		new_io;
	char			*tmp;

	if (node->state == 2)
	{
		node->state = -2;
		exec_subshell(node, &io, job);
		return (0);
	}
	new_io = (t_io_lists){NULL, NULL, 0, io.cmd};
	ret = visit(node->left, job, new_io.cmd);
	if ((tmp = cut_command(new_io.cmd, 1)))
		free(tmp);
	ret += visit(node->right, job, new_io.cmd);
	return (ret);
}
