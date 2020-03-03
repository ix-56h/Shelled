/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/03 03:08:41 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"
#include "sh.h"
#include "expansions.h"
#include "ligne.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"

void		check_args(t_sh *sh, int ac, char **av)
{
	if (ac < 2)
		return ;
	ac--;
	while (ac > 0)
	{
		if (av[ac] && av[ac][0] == '-')
		{
			if (ft_strcmp(av[ac], "--ast_draw") == 0)
				sh->f.ast_draw = 1;
		}
		ac--;
	}
}

void		process_sh(t_sh *sh)
{
	if (!lifo_empty(sh->stack.errors))
	{
		print_stack_errors(sh->stack.errors, &(sh->tok));
		gnt_standalone(0);
	}
	else
	{
		if (exec_heredoc(sh->stack.here_docs))
		{
			process_expansions(sh->node);
			if (sh->f.ast_draw)
				tree_draw(sh->node);
			//visit(sh->node, &g_job_head);
			substitution_wrapper(sh->node);
			clean_job();
		}
	}
}

int			main(int ac, char **av, char **envp)
{
	t_sh		sh;

	sh.f.ast_draw = 0;
	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	g_job_head = NULL;
	init_signal();
	while (1)
	{
		sh.input = run_line_edit();
		sh.tok = get_next_token(sh.input, sh.stack.errors);
		lifo_empty(sh.stack.errors) ? sh.node = parse_program(&sh) : 0;
		process_sh(&sh);
		if (g_exit != -1)
			break ;
		free_sh(&sh);
		re_init_sh(&sh);
	}
	free_historic();
	free_sh(&sh);
	free_env(g_env);
	free_env(g_set);
	restore_term(3);
	return (g_exit == -1 ? EXIT_SUCCESS : g_exit);
}
