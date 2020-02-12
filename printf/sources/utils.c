/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <niguinti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:13:27 by niguinti          #+#    #+#             */
/*   Updated: 2019/03/07 15:31:10 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		opt_parser(t_flags *f, const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			f->d = 1;
		else if (str[i] == '-')
			f->minus = 1;
		else if (str[i] == '+')
			f->plus = 1;
		else if (str[i] == '0')
			f->zero = 1;
		else if (str[i] == ' ')
			f->s = 1;
		else
			break ;
		i++;
	}
	return (i);
}

int		taille_parser(t_flags *f, const char *str)
{
	int		i;

	i = 0;
	f->length = 8;
	while (str[i])
	{
		if (str[i] == 'h' && f->length == L_H)
			f->length = L_HH;
		else if (str[i] == 'h')
			f->length = L_H;
		else if (str[i] == 'l' && f->length == L_L)
			f->length = L_LL;
		else if (str[i] == 'l')
			f->length = L_L;
		else if (str[i] == 'L')
			f->length = L_L;
		else if (str[i] == 'j')
			f->length = L_J;
		else if (str[i] == 'z')
			f->length = L_Z;
		else
			break ;
		i++;
	}
	return (i);
}

int		width_parser(t_flags *f, const char *str)
{
	int		i;

	i = 0;
	f->m = ft_atoi(str);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int		precision_parser(t_flags *f, const char *str)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		f->p = ft_atoi(str);
		while (str[i] && ft_isdigit(str[i]))
			i++;
		i++;
	}
	else
	{
		f->p = 0;
		i++;
	}
	return (i);
}

int		get_opts(t_flags *f, const char *str, t_counts *c)
{
	int		i;

	i = 0;
	while (str[i] && !(towp_checker(str[i], 1)))
	{
		if (towp_checker(str[i], 2) == 1)
			i += opt_parser(f, str + i);
		else if (towp_checker(str[i], 3) == 1)
			i += width_parser(f, str + i);
		else if (str[i] == '.')
			i += precision_parser(f, str + i + 1);
		else if (towp_checker(str[i], 4) == 1)
		{
			if ((f->length == 4 || f->length == 2 || f->length == 5)
					&& (c->s += i))
				return (-1);
			i += taille_parser(f, str + i);
		}
		else
			break ;
	}
	c->s += i;
	if (towp_checker(str[i], 1) && (f->c = str[i]))
		c->s++;
	return (1);
}
