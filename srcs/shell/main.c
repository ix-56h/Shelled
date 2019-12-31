/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:45:42 by niguinti          #+#    #+#             */
/*   Updated: 2019/12/31 14:29:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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
	if (sh->node != NULL)
		delete_ast((&sh->node));
	if ((sh->tok).data != NULL)
		free((sh->tok).data);
	free((sh->stack)->ar);
	free((sh->stack));
	if (sh->env)
	{
		while ((sh->env)[i])
		{
			free((sh->env)[i]);
			i++;
		}
		free((sh->env));
	}
}

int		init_shell(t_sh *sh, int ac, char **av, char **envp)
{
	if (ac < 2)
	{
		printf("Usage: ./21sh \"ls -la > output.txt\" [-ast=draw]\n");
		return (0);
	}
	check_param(av, (&sh->f));
	if (!(sh->stack = stack_creator(20, sizeof(t_staterror))))
		return (0);
	sh->node = NULL;
	sh->env = NULL;
	sh->input = av[1];
	if (!envp[0])
		sh->env = init_env(sh->env);
	else
		sh->env = cpy_env(envp);
	//cpy env and add +1 to shlvl
	if (!(sh->env))
		return (0);
	sh->tok = get_next_token(sh->input, sh->stack);
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

int main(int ac, char **av, char **envp)
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
