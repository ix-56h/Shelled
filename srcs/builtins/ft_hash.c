/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:37:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/07 23:26:59 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "builtins.h"
#include "exec.h"

t_table *new_entry(char *cmd, char *cmdpath, int nb)
{
    t_table *new;

    new = (t_table *)malloc(sizeof(t_table));
    new->key = hash_func(cmd);
    new->value = (t_entry *)malloc(sizeof(t_entry));
    new->value->count = nb;
    new->value->cmd = ft_strdup(cmd);
    new->value->cmdpath = ft_strdup(cmdpath);
    new->value->next = NULL;
    new->value->prev = NULL;
    new->next = NULL;
    new->prev = NULL;
    return(new);
}

void add_to_entry(t_entry *entry, int nb, char *cmd, char *cmdpath)
{
    t_entry *tmp;

    tmp = entry;
    while(tmp->next && ft_strcmp(tmp->cmd, cmd))
        tmp = tmp->next;
    if(ft_strcmp(tmp->cmd, cmd) == 0)
        tmp->count = (nb) ? tmp->count + 1 : 0;
    else
    {
        tmp->next = (t_entry *)malloc(sizeof(t_entry));
        tmp->next->count = nb;
        tmp->next->cmd = ft_strdup(cmd);
        tmp->next->cmdpath = ft_strdup(cmdpath);
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
    }
    
}

void    add_to_table(char *cmd, int nb)
{
    t_table *tmp;
    char *cmdpath;
    unsigned long hash;

    if(lookforbuiltin(cmd))
        return ;
    if((cmdpath = get_path(cmd)) == NULL)
        return ;
    tmp = g_hash;
    if(g_hash == NULL)
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
        tmp->next = new_entry(cmd, cmdpath, nb);
        tmp->next->prev = tmp;
    }
    
}

char *search_table(char *cmd)
{
    t_table *tmp;
    t_entry *value;
    unsigned long hash;

    hash = hash_func(cmd);
    tmp = g_hash;
    while (tmp && tmp->key != hash)
        tmp = tmp->next;
    if (tmp)
    {
        value = tmp->value;
        while(value && ft_strcmp(cmd, value->cmd))
            value = value->next;
        if (value)
            return (value->cmdpath);
    }
    return (NULL);
}

void del_entry(t_entry *entry)
{
    while(entry && entry->next)
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

void empty_table(void)
{
    while(g_hash && g_hash->next)
    {
        g_hash = g_hash->next;
        del_entry(g_hash->prev->value);
        free(g_hash->prev);
        g_hash->prev = NULL;

    }
    del_entry(g_hash->value);
    free(g_hash);
    g_hash = NULL;
}

void print_table(void)
{
    t_table *tmp;
    t_entry *value;

     tmp = g_hash;
    if (tmp)
        ft_printf("occ.\tcommand\n");
    while(tmp)
    {
        value = tmp->value;
        while(value)
        {
        ft_printf("%d\t%s\n", value->count, value->cmdpath);
        value = value->next;
        }
        tmp = tmp->next;
    }
}

int	ft_hash(char **argv, char ***env)
{
    int i;

    i = 1;
    if (argv[1] && ft_strcmp(argv[1], "-r") == 0)
        empty_table();
    else if (argv[1])
    {
        while(argv[i])
        {
            add_to_table(argv[i], 0);
            i++;
        }
    }
    else
    {
        print_table();
    }
    return (0);
}