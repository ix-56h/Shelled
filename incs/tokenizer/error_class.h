/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_class.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:37:01 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 00:16:12 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CLASS_H
# define ERROR_CLASS_H

const char	g_error_msgs_prefix[PARSE_ERROR_NEAR + 1][54] = {
	[MATCH_LEX] = "unexpected EOF while looking for matching ",
	[UNEXPECTED_TOKEN] = "syntax error near unexpected ",
	[UNRECOGNIZED_TOKEN] = "syntax error near unrecognized token ",
	[PARSE_ERROR_NEAR] = "parse error near "
};
#endif
