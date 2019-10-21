/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:15:36 by niguinti          #+#    #+#             */
/*   Updated: 2019/05/10 16:14:54 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_nbrlen_base(long long n, int base)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n / base != 0)
	{
		n = n / base;
		len++;
	}
	len++;
	return (len);
}
