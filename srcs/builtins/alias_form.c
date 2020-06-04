/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <jebrocho@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:28:36 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 12:52:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*form_algo(char c, char *arg)
{
	int	cpt;
	int	new;

	cpt = 0;
	new = 0;
	while (arg[cpt])
	{
		if (arg[cpt] == c)
		{
			new = cpt;
			while (arg[new])
			{
				arg[new] = arg[new + 1];
				new++;
			}
			arg[new] = '\0';
			cpt--;
		}
		cpt++;
	}
	return (arg);
}
