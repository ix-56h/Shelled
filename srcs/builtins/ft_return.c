/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:53:53 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/27 01:42:09 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int			ft_return(char **argv, char ***tenv)
{
	(void)tenv;
	if (count_arg(argv) > 0)
		return (ft_atoi(argv[1]));
	return (0);
}
