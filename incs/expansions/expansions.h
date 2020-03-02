/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:28:03 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/02 14:38:21 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANSIONS_H
# define FT_EXPANSIONS_H

# include "sh.h"

typedef char	*t_format_ft(char *, char *);

int			g_test;

typedef enum	e_exp_mod{ // useless now
	MOD_USE_DEFAULT,
	MOD_ASSIGN_DEFAULT,
	MOD_INDICATE_ERROR,
	MOD_USE_ALTERNATIVE,
	MOD_RM_SMALL_SUFFIX,
	MOD_RM_LARGE_SUFFIX,
	MOD_RM_SMALL_PREFIX,
	MOD_RM_LARGE_PREFIX,
	MOD_ERROR,
	MOD_MAX
}				t_exp_mod; // MOD_LENGTH en dehors

typedef struct	s_exp_param
{
	t_exp_mod		mod;
	char			*s;
	t_format_ft		*ft;
}				t_exp_param;

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
char	*process_simple_parameter(size_t *i, char *word);

/*
**	substitution.c functions
*/
char	*process_substitution(size_t *i, char *word);

/*
**	utils/index_end_squote.c
*/
int		index_end_squote(char *w, int i);

/*
**	parameter_expansions.c
*/
char	*use_default_value(char *param, char *word);
char	*assign_default_value(char *param, char *word);
char	*indicate_error(char *param, char *word);
char	*use_alternative_value(char *param, char *word);
char	*show_string_length(char *param, char *word);

/*
**	parameter_expansions2.c
*/
char	*remove_small_suffix(char *param, char *word);
char	*remove_large_suffix(char *param, char *word);
char	*remove_small_prefix(char *param, char *word);
char	*remove_large_prefix(char *param, char *word);

/*
**	expansions_utils.c
*/
char	*remove_brace(char *word);
char	*get_expansion_format(size_t *i, char *word);
char	*error_test(char *param, char *word);

/*
**	dispatch_expansions.c
*/
char	*dispatch_exp(char *full_word, char *mod);

#endif









