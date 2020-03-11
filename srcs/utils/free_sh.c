/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:49:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/08 23:57:19 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_sh(t_sh *sh)
{
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
