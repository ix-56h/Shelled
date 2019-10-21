/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:54:10 by niguinti          #+#    #+#             */
/*   Updated: 2018/11/21 14:22:55 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;
	t_list *newfirst;
	t_list *current;

	if (!lst || !*f)
		return (NULL);
	newfirst = NULL;
	while (lst)
	{
		newlst = (f)(lst);
		if (newfirst)
		{
			current->next = newlst;
			current = current->next;
		}
		else
		{
			newfirst = newlst;
			current = newfirst;
		}
		lst = lst->next;
	}
	return (newfirst);
}
