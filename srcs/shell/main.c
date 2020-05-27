/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/05/23 14:52:21 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "visitor.h"
#include "sh.h"
#include "expansions.h"
#include "ligne.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"

void		init_shell_job(void)
{
	int	shell_is_interactive;
	int	shell_terminal;

	shell_terminal = 0;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive)
	{
    	while (tcgetpgrp(shell_terminal) != (g_shell_pgid = getpgrp()))
		{
    		kill(-g_shell_pgid, SIGTTIN);
		}
		signal (SIGINT, SIG_IGN);
    	signal (SIGQUIT, SIG_IGN);
    	signal (SIGTSTP, SIG_IGN);
    	signal (SIGTTIN, SIG_IGN);
    	signal (SIGTTOU, SIG_IGN);
		set_up_sigchld();
    	g_shell_pgid = getpid ();
    	if (setpgid (g_shell_pgid, g_shell_pgid) < 0)
    	{
        	ft_putstr_fd("Couldn't put the shell in its own process group", STDERR_FILENO);
    		exit(1);
        }
    	tcsetpgrp (shell_terminal, g_shell_pgid);
    }
}


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
	char	*cmd;

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
			cmd = ft_strdup(sh->input);
			visit(sh->node, &g_job_head, cmd);
			free(cmd);
		}
	}
	clean_job();
}

int			main(int ac, char **av, char **envp)
{
	t_sh		sh;

	sh.f.ast_draw = 0;
	init_shell_job();
	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	g_job_head = NULL;
	g_jobnb = NULL;
	init_signal();
	while (1)
	{
		do_job_notification();
		sh.input = run_line_edit();
		sh.input = add_alias(sh.input, sh.stack.errors);
		sh.tok = get_next_token(sh.input, sh.stack.errors);
		lifo_empty(sh.stack.errors) ? sh.node = parse_program(&sh) : 0;
		process_sh(&sh);
		if (g_exit != -1)
			break ;
		free_sh(&sh);
		re_init_sh(&sh);
	}
	oprhaned_jobs();
	free_historic();
	free_sh(&sh);
	free_env(g_env);
	free_env(g_set);
	restore_term(1);
	return (g_exit == -1 ? EXIT_SUCCESS : g_exit);
}
