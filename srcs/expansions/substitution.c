/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:14:52 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 16:41:37 by niguinti         ###   ########.fr       */
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
	//t_sh		sh;
	(void)tmp;
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
		if (!(nw = malloc((sizeof(char) * y) + 1)))
			exit(1);
		ft_strncpy(nw, word + *i, y);
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
