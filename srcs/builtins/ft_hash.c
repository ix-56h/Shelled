/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:37:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/11 15:38:35 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "builtins.h"
#include "exec.h"

void	del_entry(t_entry *entry)
{
	while (entry && entry->next)
	{
		ft_strdel(&(entry->cmd));
		ft_strdel(&(entry->cmdpath));
		entry = entry->next;
		free(entry->prev);
		entry->prev = NULL;
	}
	ft_strdel(&(entry->cmd));
	ft_strdel(&(entry->cmdpath));
	free(entry);
	entry = NULL;
}

void	empty_table(void)
{
	while (g_hash && g_hash->next)
	{
		g_hash = g_hash->next;
		del_entry(g_hash->prev->value);
		free(g_hash->prev);
		g_hash->prev = NULL;
	}
	if (g_hash)
	{
		del_entry(g_hash->value);
		free(g_hash);
		g_hash = NULL;
	}
}

void	print_table(void)
{
	t_table *tmp;
	t_entry *value;

	tmp = g_hash;
	if (tmp)
		ft_printf("hits\tcommand\n");
	while (tmp)
	{
		value = tmp->value;
		while (value)
		{
			ft_printf("%d\t%s\n", value->count, value->cmdpath);
			value = value->next;
		}
		tmp = tmp->next;
	}
}

int		ft_hash(char **argv, char ***env)
{
	int i;

	(void)env;
	i = 1;
	if (argv[1] && ft_strcmp(argv[1], "-r") == 0)
		empty_table();
	else if (argv[1])
	{
		while (argv[i])
		{
			add_to_table(argv[i], 0);
			i++;
		}
	}
	else
		print_table();
	return (0);
}
