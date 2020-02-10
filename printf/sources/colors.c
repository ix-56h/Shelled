/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:07:18 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/15 15:17:07 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	regular_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "BLACK") == 0 && (tmp = 1))
		write_str(buf, c, BLACK);
	else if (ft_strcmp(color, "RED") == 0 && (tmp = 1))
		write_str(buf, c, RED);
	else if (ft_strcmp(color, "GREEN") == 0 && (tmp = 1))
		write_str(buf, c, GREEN);
	else if (ft_strcmp(color, "YELLOW") == 0 && (tmp = 1))
		write_str(buf, c, YELLOW);
	else if (ft_strcmp(color, "BLUE") == 0 && (tmp = 1))
		write_str(buf, c, BLUE);
	else if (ft_strcmp(color, "PURPLE") == 0 && (tmp = 1))
		write_str(buf, c, PURPLE);
	else if (ft_strcmp(color, "CYAN") == 0 && (tmp = 1))
		write_str(buf, c, CYAN);
	else if (ft_strcmp(color, "WHITE") == 0 && (tmp = 1))
		write_str(buf, c, WHITE);
	return (tmp);
}

int	bold_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "BBLACK") == 0 && (tmp = 1))
		write_str(buf, c, BBLACK);
	else if (ft_strcmp(color, "BRED") == 0 && (tmp = 1))
		write_str(buf, c, BRED);
	else if (ft_strcmp(color, "BGREEN") == 0 && (tmp = 1))
		write_str(buf, c, BGREEN);
	else if (ft_strcmp(color, "BYELLOW") == 0 && (tmp = 1))
		write_str(buf, c, BYELLOW);
	else if (ft_strcmp(color, "BBLUE") == 0 && (tmp = 1))
		write_str(buf, c, BBLUE);
	else if (ft_strcmp(color, "BPURPLE") == 0 && (tmp = 1))
		write_str(buf, c, BPURPLE);
	else if (ft_strcmp(color, "BCYAN") == 0 && (tmp = 1))
		write_str(buf, c, BCYAN);
	else if (ft_strcmp(color, "BWHITE") == 0 && (tmp = 1))
		write_str(buf, c, BWHITE);
	return (tmp);
}

int	underline_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "UBLACK") == 0 && (tmp = 1))
		write_str(buf, c, UBLACK);
	else if (ft_strcmp(color, "URED") == 0 && (tmp = 1))
		write_str(buf, c, URED);
	else if (ft_strcmp(color, "UGREEN") == 0 && (tmp = 1))
		write_str(buf, c, UGREEN);
	else if (ft_strcmp(color, "UYELLOW") == 0 && (tmp = 1))
		write_str(buf, c, UYELLOW);
	else if (ft_strcmp(color, "UBLUE") == 0 && (tmp = 1))
		write_str(buf, c, UBLUE);
	else if (ft_strcmp(color, "UPURPLE") == 0 && (tmp = 1))
		write_str(buf, c, UPURPLE);
	else if (ft_strcmp(color, "UCYAN") == 0 && (tmp = 1))
		write_str(buf, c, UCYAN);
	else if (ft_strcmp(color, "UWHITE") == 0 && (tmp = 1))
		write_str(buf, c, UWHITE);
	return (tmp);
}
