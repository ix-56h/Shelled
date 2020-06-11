/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:38:33 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/11 15:37:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "sh.h"
# include "libft.h"
# include "ft_printf.h"

typedef	struct		s_entry
{
	char			*cmd;
	char			*cmdpath;
	int				count;
	struct s_entry	*next;
	struct s_entry	*prev;
}					t_entry;

typedef struct		s_table
{
	unsigned long	key;
	t_entry			*value;
	struct s_table	*next;
	struct s_table	*prev;
}					t_table;

t_table				*g_hash;

char				*search_in_table(char *cmd);
void				add_to_table(char *cmd, int nb);
char				*search_table(char *cmd);
unsigned long		hash_func(char *str);
char				*get_path(char *cmd);
void				empty_table(void);

#endif
