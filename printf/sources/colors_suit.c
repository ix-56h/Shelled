/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:07:18 by niguinti          #+#    #+#             */
/*   Updated: 2019/04/15 15:19:52 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		background_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "ON_BLACK") == 0 && (tmp = 1))
		write_str(buf, c, ON_BLACK);
	else if (ft_strcmp(color, "ON_RED") == 0 && (tmp = 1))
		write_str(buf, c, ON_RED);
	else if (ft_strcmp(color, "ON_GREEN") == 0 && (tmp = 1))
		write_str(buf, c, ON_GREEN);
	else if (ft_strcmp(color, "ON_YELLOW") == 0 && (tmp = 1))
		write_str(buf, c, ON_YELLOW);
	else if (ft_strcmp(color, "ON_BLUE") == 0 && (tmp = 1))
		write_str(buf, c, ON_BLUE);
	else if (ft_strcmp(color, "ON_PURPLE") == 0 && (tmp = 1))
		write_str(buf, c, ON_PURPLE);
	else if (ft_strcmp(color, "ON_CYAN") == 0 && (tmp = 1))
		write_str(buf, c, ON_CYAN);
	else if (ft_strcmp(color, "ON_WHITE") == 0 && (tmp = 1))
		write_str(buf, c, ON_WHITE);
	return (tmp);
}

int		high_intensity_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "IBLACK") == 0 && (tmp = 1))
		write_str(buf, c, IBLACK);
	else if (ft_strcmp(color, "IRED") == 0 && (tmp = 1))
		write_str(buf, c, IRED);
	else if (ft_strcmp(color, "IGREEN") == 0 && (tmp = 1))
		write_str(buf, c, IGREEN);
	else if (ft_strcmp(color, "IYELLOW") == 0 && (tmp = 1))
		write_str(buf, c, IYELLOW);
	else if (ft_strcmp(color, "IBLUE") == 0 && (tmp = 1))
		write_str(buf, c, IBLUE);
	else if (ft_strcmp(color, "IPURPLE") == 0 && (tmp = 1))
		write_str(buf, c, IPURPLE);
	else if (ft_strcmp(color, "ICYAN") == 0 && (tmp = 1))
		write_str(buf, c, ICYAN);
	else if (ft_strcmp(color, "IWHITE") == 0 && (tmp = 1))
		write_str(buf, c, IWHITE);
	return (tmp);
}

int		bold_intensity_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "BIBLACK") == 0 && (tmp = 1))
		write_str(buf, c, BIBLACK);
	else if (ft_strcmp(color, "BIRED") == 0 && (tmp = 1))
		write_str(buf, c, BIRED);
	else if (ft_strcmp(color, "BIGREEN") == 0 && (tmp = 1))
		write_str(buf, c, BIGREEN);
	else if (ft_strcmp(color, "BIYELLOW") == 0 && (tmp = 1))
		write_str(buf, c, BIYELLOW);
	else if (ft_strcmp(color, "BIBLUE") == 0 && (tmp = 1))
		write_str(buf, c, BIBLUE);
	else if (ft_strcmp(color, "BIPURPLE") == 0 && (tmp = 1))
		write_str(buf, c, BIPURPLE);
	else if (ft_strcmp(color, "BICYAN") == 0 && (tmp = 1))
		write_str(buf, c, BICYAN);
	else if (ft_strcmp(color, "BIWHITE") == 0 && (tmp = 1))
		write_str(buf, c, BIWHITE);
	return (tmp);
}

int		high_intensity_bg_color(char *buf, char *color, t_counts *c)
{
	int tmp;

	tmp = 0;
	if (ft_strcmp(color, "ON_IBLACK") == 0 && (tmp = 1))
		write_str(buf, c, ON_IBLACK);
	else if (ft_strcmp(color, "ON_IRED") == 0 && (tmp = 1))
		write_str(buf, c, ON_IRED);
	else if (ft_strcmp(color, "ON_IGREEN") == 0 && (tmp = 1))
		write_str(buf, c, ON_IGREEN);
	else if (ft_strcmp(color, "ON_IYELLOW") == 0 && (tmp = 1))
		write_str(buf, c, ON_IYELLOW);
	else if (ft_strcmp(color, "ON_IBLUE") == 0 && (tmp = 1))
		write_str(buf, c, ON_IBLUE);
	else if (ft_strcmp(color, "ON_IPURPLE") == 0 && (tmp = 1))
		write_str(buf, c, ON_IPURPLE);
	else if (ft_strcmp(color, "ON_ICYAN") == 0 && (tmp = 1))
		write_str(buf, c, ON_ICYAN);
	else if (ft_strcmp(color, "ON_IWHITE") == 0 && (tmp = 1))
		write_str(buf, c, ON_IWHITE);
	return (tmp);
}

void	read_color(char *buf, const char *str, t_counts *c)
{
	char	color[10];
	int		i;
	int		tmp;

	tmp = 0;
	i = 0;
	ft_bzero(color, sizeof(color));
	(str[++(c->s)] == '/') ? tmp = 1 : 0;
	while (i < 10 && str[c->s] != '}' && str[c->s])
		color[i++] = ft_toupper(str[(c->s++)]);
	(str[c->s] == '}') ? c->s += 1 : 0;
	if (tmp)
	{
		write_str(buf, c, END_COLOR);
		return ;
	}
	tmp = regular_color(buf, color, c);
	tmp == 0 ? tmp = bold_color(buf, color, c) : 0;
	tmp == 0 ? tmp = underline_color(buf, color, c) : 0;
	tmp == 0 ? tmp = background_color(buf, color, c) : 0;
	tmp == 0 ? tmp = high_intensity_color(buf, color, c) : 0;
	tmp == 0 ? tmp = bold_intensity_color(buf, color, c) : 0;
	tmp == 0 ? tmp = high_intensity_bg_color(buf, color, c) : 0;
	tmp == 0 ? c->s -= i + 2 : 0;
}
