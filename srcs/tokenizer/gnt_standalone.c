/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnt_standalone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:55:09 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/03 01:55:10 by niguinti         ###   ########.fr       */
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
