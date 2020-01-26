/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 02:53:24 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/29 03:27:31 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*erase_char(char *str)
{
	if (str[0] != '\0')
		ft_strcpy(str, str + 1);
	return (str);
}