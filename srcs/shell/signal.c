/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 20:01:04 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/09 23:01:25 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ligne.h"

static void	usless(int n)
{
	(void)n;
}

static void	signal_handler(int n)
{
	restore_term();
	exit(n);
}

void		init_singal(void)
{
	int		i;

	i = 0;
    signal(SIGTSTP, usless);
	while (++i <= 15)
		signal(i, &signal_handler);
	signal(24, &signal_handler);
	signal(25, &signal_handler);
	signal(26, &signal_handler);
	signal(27, &signal_handler);
	signal(30, &signal_handler);
	signal(31, &signal_handler);
}