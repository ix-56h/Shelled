/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/03 03:42:24 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"
#include "visitor.h"

#include <stdlib.h>
char	*exec_substitution(char *tmp)
{
	t_sh		sh;
	char		*nw;

	if (!(sh.stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return (0);
	sh.node = NULL;
	sh.input = tmp;
	sh.tok = get_next_token(sh.input, sh.stack.errors);
	lifo_empty(sh.stack.errors) ? sh.node = parse_command(&sh) : 0;
	if (!lifo_empty(sh.stack.errors))
	{
		print_stack_errors(sh.stack.errors, &sh.tok);
		return (ft_strdup(""));
	}
	nw = substitution_wrapper(sh.node);
	nw = ft_strtrimf(nw);
	tree_draw(sh.node);
	free(sh.stack.errors->ar);
	free(sh.stack.errors);
	if (sh.node != NULL)
		delete_ast(&sh.node);
	if ((sh.tok).data != NULL)
		free((sh.tok).data);
	return (nw);
}

char	*process_substitution(size_t *i, char *word)
{
	size_t	y;
	char	*tmp;
	char	*nw;

	y = *i;
	while (word[y] && word[y] != ')')
		y++;
	if (!word[y])
		return (0);
	if (word[y] == ')')
	{
		if (!(nw = ft_memalloc((sizeof(char) * y))))
			exit(1);
		ft_strncpy(nw, word + *i + 1, y - 2);
		tmp = exec_substitution(nw);
		free(nw);
		word[*i - 1] = 0;
		nw = ft_vjoin(3, word, tmp, word + y + 1);
		free(tmp);
		free(word);
	}
	else
		return (word);
	return (nw);
}
