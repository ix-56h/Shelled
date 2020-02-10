/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/10 11:14:42 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"
#include "sh.h"
#include "expansions.h"
#include "ligne.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"

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
			tree_draw(sh->node);
			visit(sh->node);
		}
	}
}

int			main(int ac, char **av, char **envp)
{
	t_sh		sh;

	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	init_singal();
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
	return (g_exit == -1 ? EXIT_SUCCESS : g_exit);
}
