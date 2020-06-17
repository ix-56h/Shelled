/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 18:52:04 by akeiflin          #+#    #+#             */
/*   Updated: 2020/06/13 01:35:30 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "ligne.h"
#include "visitor.h"
#include "sh.h"
#include "parser.h"

static void		substitution_fork(char *str, int *pipefd, int *stdout_save)
{
	int		pid;
	t_sh	sh;

	if ((pid = fork()) == -1)
	{
		close(pipefd[READ_END]);
		dup2(*stdout_save, STDOUT_FILENO);
		return ;
	}
	else if (pid == 0)
	{
		if (!(sh.stack.errors = lifo_creator(20, sizeof(t_staterror))))
			exit(1);
		sh.node = NULL;
		sh.input = str;
		sh.tok = get_next_token(sh.input, sh.stack.errors);
		lifo_empty(sh.stack.errors) ? sh.node = parse_complete_command(&sh) : 0;
		if (!lifo_empty(sh.stack.errors))
			exit(1);
		close(pipefd[READ_END]);
		visit(sh.node, NULL, NULL);
		exit(0);
	}
}

static void		substituton_exec(int *pipefd, char *str)
{
	int		stdout_save;
	int		status;

	stdout_save = dup(STDOUT_FILENO);
	dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[WRITE_END]);
	signal(SIGCHLD, SIG_DFL);
	substitution_fork(str, &(pipefd[0]), &stdout_save);
	waitpid(WAIT_ANY, &status, WUNTRACED);
	set_up_sigchld();
	dup2(stdout_save, STDOUT_FILENO);
}

char			*substitution_wrapper(char *str)
{
	int		pipefd[2];
	char	*ret;
	char	buff[BUFFSIZE + 1];

	if (pipe(pipefd) != -1 && (ret = NULL) == NULL)
	{
		substituton_exec(&(pipefd[0]), str);
		ft_bzero(buff, sizeof(char) * (BUFFSIZE + 1));
		while (read(pipefd[READ_END], buff, BUFFSIZE) > 0)
		{
			if (ret)
				ret = ft_strjoinf(ret, buff, 1);
			else
				ret = ft_strdup(buff);
			ft_bzero(buff, sizeof(char) * (BUFFSIZE + 1));
		}
		close(pipefd[READ_END]);
		return (ret);
	}
	return (NULL);
}
