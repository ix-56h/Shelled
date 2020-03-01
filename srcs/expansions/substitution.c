/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/01 05:18:00 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visitor.h"
#include "sh.h"
#include "expansions.h"
#include "ligne.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"

char	*exec_substitution(char *tmp)
{
	t_sh		sh;
	
	if (!(sh.stack.errors = lifo_creator(20, sizeof(t_staterror))))
		return (0);
	sh.node = NULL;
	sh.input = tmp;
	sh.tok = get_next_token(sh.input, sh.stack.errors);
	lifo_empty(sh.stack.errors) ? sh.node = parse_command(&sh) : 0;
	if (!lifo_empty(sh.stack.errors))
	{
		print_stack_errors(sh.stack.errors, &sh.tok);
		return (ft_strdup("FAILED"));
	}
	tree_draw(sh.node);
	return (ft_strdup("COMMAND"));
}

char	*process_substitution(size_t *i, char *word)
{
	size_t	y;
	char	*tmp;
	char	*nw;

	y = *i;
	while (word[y] && word[y] != ')')
		y++;
	if (word[y] == ')')
	{
		if (!(nw = ft_memalloc((sizeof(char) * y))))
			exit(1);
		ft_strncpy(nw, word + *i, y - 1);
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
