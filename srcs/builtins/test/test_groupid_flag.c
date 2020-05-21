/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_groupid_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		test_groupid_flag(char *s1, char *s2)
{
	(void)s2;
	if (stat(s1, &st) < 0)
		return (1);
	if (st.st_mode & S_ISGID)
		return (0);
	return (1);
}
