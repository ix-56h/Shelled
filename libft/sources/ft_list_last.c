/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:16:22 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 14:17:13 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_last(t_list *alst)
{
	while (alst != NULL)
	{
		if (alst->next == NULL)
			return (alst);
		else
			alst = alst->next;
	}
	return (alst);
}
