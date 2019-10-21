/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:13:10 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 14:15:44 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_find(t_list *alst, void *data_ref, int (*cmp)())
{
	while (alst)
	{
		if ((*cmp)(data_ref, alst->content) == 0)
			return (alst);
		alst = alst->next;
	}
	return (NULL);
}
