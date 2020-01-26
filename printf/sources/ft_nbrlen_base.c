/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:15:36 by niguinti          #+#    #+#             */
/*   Updated: 2019/02/21 18:35:30 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_nbrlen_base(long long n, int base)
{
	int		len;

	len = 0;
	while ((n /= base) >= 1)
		len++;
	return (len);
}