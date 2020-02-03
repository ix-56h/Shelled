/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standalone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:42:45 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/03 02:58:08 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_gnt	*gnt_standalone(size_t value)
{
	static t_gnt	gnt;

	if (!value)
		ft_bzero(&gnt, sizeof(gnt));
	return (&gnt);
}
