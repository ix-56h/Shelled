/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:49:53 by ezonda            #+#    #+#             */
/*   Updated: 2020/03/09 03:58:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "expansions.h"

void			get_multi_pos_param(char **word)
{
	int		i;
	int		j;
	char	param[256];
	char	**split;

	j = 0;
	i = 1;
	if (!get_env(g_set, "@"))
		return ;
	split = ft_strsplit(get_env(g_set, "@"), ' ');
	while ((*word)[i])
	{
		param[j] = (*word)[i];
		j++;
		i++;
	}
	param[j] = '\0';
	i = ft_atoi(param);
	look_multi_pos_param(split, word, i);
}

int				digit_error(char *word)
{
	size_t i;

	i = 0;
	while (ft_isalpha(word[i]))
		i++;
	if (i == ft_strlen(word))
		return (0);
	while (word[i] != '$')
		i++;
	i = word[i] == '{' ? i + 2 : i + 1;
	if (word[i + 1] == '\0' && (word[i] == '?' || word[i] == '-'
	|| word[i] == '@' || word[i] == '!' || word[i] == '*' || word[i] == '$'
	|| word[i] == '#'))
		return (0);
	if ((ft_isdigit(word[i]) && !ft_isalldigit(&word[i]))
		|| (!ft_isalnum(word[i])))
	{
		ft_putstr_fd("42sh: bad substitution\n", 2);
		g_exp_error = 1;
		add_set("?", "1");
		return (1);
	}
	return (0);
}

char			*test_without_modifier(char *word)
{
	int		i;
	char	*new_word;

	i = 1;
	new_word = remove_brace(word);
	if (!new_word[0])
	{
		free(new_word);
		return (ft_strdup(""));
	}
	if (ft_isalldigit(&new_word[1]) && new_word[1] != '0')
		get_multi_pos_param(&new_word);
	if (!new_word[0])
		return (new_word);
	if (digit_error(new_word))
		ft_bzero(new_word, ft_strlen(new_word));
	while (new_word[i++])
		if (parameter_error(new_word, i, 1))
			return (ft_strdup(""));
	new_word = expand_word(new_word);
	return (new_word);
}

char			*test_parameter(t_exp_data *exp, char *word)
{
	char	*new_word;

	new_word = NULL;
	if (exp->last[0])
		process_expression(&exp->last);
	if (!exp->modifier)
		new_word = test_without_modifier(word);
	else
	{
		new_word = dispatch_exp(word, exp->modifier);
		if (exp->first[0])
			new_word = ft_strjoinf(exp->first, new_word, 2);
	}
	if (exp->last[0] && !is_blank(exp->last))
		new_word = ft_strjoinf(new_word, exp->last, 1);
	return (new_word);
}
