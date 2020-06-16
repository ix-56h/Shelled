/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:17:41 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/16 15:36:02 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "builtins.h"
#include "exec.h"

t_table	*new_entry(char *cmd, char *cmdpath, int nb)
{
	t_table *new;

	if (!(new = (t_table *)malloc(sizeof(t_table))))
		return (NULL);
	new->key = hash_func(cmd);
	if (!(new->value = (t_entry *)malloc(sizeof(t_entry))))
	{
		free(new);
		return (NULL);
	}
	new->value->count = nb;
	new->value->cmd = ft_strdup(cmd);
	new->value->cmdpath = cmdpath;
	new->value->next = NULL;
	new->value->prev = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_entry(t_entry *entry, int nb, char *cmd, char *cmdpath)
{
	t_entry *tmp;

	tmp = entry;
	while (tmp->next && ft_strcmp(tmp->cmd, cmd))
		tmp = tmp->next;
	if (ft_strcmp(tmp->cmd, cmd) == 0)
	{
		tmp->count = (nb) ? tmp->count + 1 : 0;
		ft_strdel(&cmdpath);
	}
	else
	{
		if (!(tmp->next = (t_entry *)malloc(sizeof(t_entry))))
			return ;
		tmp->next->count = nb;
		tmp->next->cmd = ft_strdup(cmd);
		tmp->next->cmdpath = cmdpath;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}
}

void	add_to_table(char *cmd, int nb)
{
	t_table			*tmp;
	char			*cmdpath;
	unsigned long	hash;

	if (lookforbuiltin(cmd) || !(cmdpath = get_path(cmd)))
		return ;
	tmp = g_hash;
	if (g_hash == NULL)
	{
		g_hash = new_entry(cmd, cmdpath, nb);
		return ;
	}
	hash = hash_func(cmd);
	while (tmp->next && hash != tmp->key)
		tmp = tmp->next;
	if (hash == tmp->key)
		add_to_entry(tmp->value, nb, cmd, cmdpath);
	else
	{
		if (!(tmp->next = new_entry(cmd, cmdpath, nb)))
			return ;
		tmp->next->prev = tmp;
	}
}

char	*search_table(char *cmd)
{
	t_table			*tmp;
	t_entry			*value;
	unsigned long	hash;

	hash = hash_func(cmd);
	tmp = g_hash;
	while (tmp && tmp->key != hash)
		tmp = tmp->next;
	if (tmp)
	{
		value = tmp->value;
		while (value && ft_strcmp(cmd, value->cmd))
			value = value->next;
		if (value)
			return (value->cmdpath);
	}
	return (NULL);
}
