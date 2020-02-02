/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:28:03 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 05:22:55 by niguinti         ###   ########.fr       */
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
int		find_quotes(char *s);
void	quote_removal(char **w);

/*
**	expression.c functions
*/
void	process_expression(char **w);
#endif
