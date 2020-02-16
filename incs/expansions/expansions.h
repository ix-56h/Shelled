/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:28:03 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/16 02:50:38 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANSIONS_H
# define FT_EXPANSIONS_H

/*
**	expansions.c functions
*/

void	process_expansions(t_node *n);

/*
**	quote_removal.c functions
*/
char	*find_squotes_end(char *w);
int		find_quotes(char *s);
void	quote_removal(char **w);

/*
**	expression.c functions
*/
void	process_expression(char **w);

/*
**	utils/index_end_squote.c
*/
int		index_end_squote(char *w, int i);
#endif
