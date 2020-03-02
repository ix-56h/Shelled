/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:05:56 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/25 19:12:00 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "tokenizer.h"

typedef	struct		s_node
{
	struct s_node	*left;
	int				state;
	int				id;
	int				io;

	char			**args;

	int				capacity;
	int				cur_size;
	int				cur_i;

	t_toktype		tok;
	char			*data;
	struct s_node	*right;
}					t_node;
#endif
