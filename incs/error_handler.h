/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:12 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 02:01:50 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_HANDLER_H
# define FT_ERROR_HANDLER_H
# include "stack.h"

/*
**	parse_error.c
*/
void		print_stack_errors(t_lifo *stack, t_tokens *cur);
int			error_push(t_lifo *stack, int type, char *near);
#endif
