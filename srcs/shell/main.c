/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/02 21:56:19 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sh.h>
#include "ligne.h"

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

void		free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		++i;
	}
	if (env && env[i])
		free(env[i]);
	free(env);
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
	free((sh->stack)->ar);
	free((sh->stack));
}

int		init_shell(t_sh *sh, int ac, char **av, char **envp)
{
	check_param(av, (&sh->f));
	if (!(sh->stack = stack_creator(20, sizeof(t_staterror))))
		return (0);
	sh->node = NULL;
	sh->env = NULL;
	if (!envp[0])
		sh->env = init_env(sh->env);
	else
		sh->env = cpy_env(envp);
	//cpy env and add +1 to shlvl
	if (!(sh->env))
		return (0);
	init_term();
	signal(SIGWINCH, &handle_resize);
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
	}
}

void	re_init_sh(t_sh *sh)
{
	if (!(sh->stack = stack_creator(20, sizeof(t_staterror))))
		return ;
	sh->node = NULL;
	sh->env = NULL;
}

int main(int ac, char **av, char **envp)
{
	t_sh		sh;
	t_dl_node		*head;
	t_line			*line;

	head = NULL;
	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	while (1)
	{
		sh.input = run_line_edit();
		sh.tok = get_next_token(sh.input, sh.stack);
		if (is_int_empty(sh.stack))
			sh.node = parse_program(sh.input, &(sh.tok), sh.stack);
			
		// pour l'exit, on va voir de peut-etre faire une global voir 
		if (ft_strcmp(sh.input, "exit") == 0) //stop temporaire???
			break;

		if (!is_int_empty(sh.stack))
		{
			print_stack_errors(sh.stack, &(sh.tok), sh.input);
			free_sh(&sh);
			return (EXIT_FAILURE);
		}
		else
			visit(sh.node);	
		free_sh(&sh);
		re_init_sh(&sh);
	}
	free_historic();
	tree_draw(sh.node, sh.f);
	free_sh(&sh);
	free_env(sh.env);
	close(0);close(1);close(2); // a des fin de debug
	return (EXIT_SUCCESS);
}

/*int main(int ac, char **av, char **envp)
{
	t_sh		sh;

	if (init_shell(&sh, ac, av, envp) == 0)
		return (EXIT_FAILURE);
	if (is_int_empty(sh.stack))
		sh.node = parse_program(sh.input, &(sh.tok), sh.stack);
	if (!is_int_empty(sh.stack))
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
