/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:49:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 06:00:48 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
