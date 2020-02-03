/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:16:28 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/03 01:01:24 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "historique.h"
#include "double_linked_list.h"

int					historic_on_use(int act)
{
	static int on_use;

	if (act == 1)
		on_use = 1;
	else if (act == 2)
		on_use = 0;
	return (on_use);
}

t_historic			**get_historic(void)
{
	static t_historic *historic = NULL;

	return (&historic);
}
