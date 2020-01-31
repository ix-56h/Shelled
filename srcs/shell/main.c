/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/01 00:20:58 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "visitor.h"
#include "sh.h"
#include "expansions.h"
#include "ligne.h"
#include "parser.h"

void	check_param(char **av, t_flags *f)
{
	f->ast_draw = 0;
	while (*av)
	{
		if (strcmp(*av, "-ast=draw") == 0)
			f->ast_draw = 1;
		av++;
	}
}

void	free_sh(t_sh *sh)
{
	size_t	i;

	i = 0;
	if (sh->input)
		free(sh->input);
	sh->input = NULL;
	if (sh->node != NULL)
		delete_ast((&sh->node));
	if ((sh->tok).data != NULL)
		free((sh->tok).data);
	free((sh->stack.errors->ar));
	free((sh->stack.errors));
	free(sh->stack.here_docs->ar);
	free(sh->stack.here_docs);
}

int		init_shell(t_sh *sh, int ac, char **av, char **envp)
{
	g_exit = -1;
	check_param(av, (&sh->f));
	if (!(sh->stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return (0);
	if (!(sh->stack.here_docs = fifo_creator(20, sizeof(t_node*))))
		return (0);
	sh->node = NULL;
	g_env = NULL;
	if (!envp[0])
		g_env = init_env(g_env);
	else
		g_env = cpy_env(envp);
	//cpy env and add +1 to shlvl
	if (!g_env)
		return (0);
	init_term();
	//signal(SIGWINCH, &handle_resize);
	return (1);
}

void	tree_draw(t_node *node, t_flags f)
{
	if (f.ast_draw)
	{
		FILE *stream = fopen("tree.dot", "w");
		if (!stream)
			exit(0);
		bst_print_dot(node, stream);
		fclose(stream);
	}
}

void	re_init_sh(t_sh *sh)
{
	if (!(sh->stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return ;
	if (!(sh->stack.here_docs = fifo_creator(20, sizeof(t_node*))))
		return ;
	sh->node = NULL;
}

int main(int ac, char **av, char **envp)
{
	t_sh		sh;
	t_dl_node		*head;

	head = NULL;
	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	while (1)
	{
		sh.input = run_line_edit();
		sh.tok = get_next_token(sh.input, sh.stack.errors);
		if (lifo_empty(sh.stack.errors))
			sh.node = parse_program(&sh);
		if (!lifo_empty(sh.stack.errors))
		{
			print_stack_errors(sh.stack.errors, &(sh.tok), sh.input);
			free_sh(&sh);
			return (EXIT_FAILURE);
		}
		else
		{
			if (exec_heredoc(sh.stack.here_docs))
			{
				process_expansions(sh.node);
				tree_draw(sh.node, sh.f);
				visit(sh.node);	
			}
		}
		if (g_exit != -1)
			break;
		free_sh(&sh);
		re_init_sh(&sh);
	}
	free_historic();
	free_sh(&sh);
	free_env(g_env);
	return (g_exit == -1 ? EXIT_SUCCESS : g_exit);
}

/*int main(int ac, char **av, char **envp)
{
	t_sh		sh;

	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	if (lifo_empty(sh.stack))
		sh.node = parse_program(sh.input, &(sh.tok), sh.stack);
	if (!lifo_empty(sh.stack))
	{
		print_stack_errors(sh.stack, &(sh.tok), sh.input);
		free_sh(&sh);
		return (EXIT_FAILURE);
	}
	else
		visit(sh.node);
	tree_draw(sh.node, sh.f);
	free_sh(&sh);
	return (EXIT_SUCCESS);
}
*/
