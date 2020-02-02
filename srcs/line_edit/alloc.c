/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:58:38 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/02 23:56:47 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ligne.h"

t_dl_node	*dup_line_node(t_dl_node *src)
{
	t_dl_node	*head;
	t_dl_node	*link;
	t_line		*new_line;
	t_line		*tmp_line;

	head = NULL;
	link = NULL;
	new_line = NULL;
	if (!src)
		return (NULL);
	while (src)
	{
		tmp_line = src->data;
		new_line = init_line(NULL, ft_strdup(tmp_line->line)\
				, ft_strlen(tmp_line->line), dup_prompt(tmp_line->prompt));
		new_line->no_newline = tmp_line->no_newline;
		dl_append(&link, new_line);
		if (!head)
			head = link;
		src = src->next;
	}
	return (head);
}

t_prompt	*dup_prompt(t_prompt *src)
{
	t_prompt	*new_prompt;

	if (!(new_prompt = malloc(sizeof(t_prompt))))
		return (ft_throw_err_free(0));
	if (!(new_prompt->str = ft_strdup(src->str)))
		return (ft_throw_err_free(1, new_prompt));
	new_prompt->size = src->size;
	return (new_prompt);
}

t_line		*init_line(t_line *tline, char *line, int index, t_prompt *prompt)
{
	if (!tline)
		tline = ft_calloc(sizeof(t_line));
	if (!tline)
		return (NULL);
	if (!line)
	{
		tline->line = ft_calloc(sizeof(char) * (BUFFSIZE + 1));
		tline->allocsize = BUFFSIZE;
	}
	else
	{
		tline->line = line;
		tline->allocsize = ft_strlen(line);
	}
	tline->index = index;
	tline->prompt = prompt;
	tline->no_newline = 0;
	return (tline);
}

t_prompt	*new_prompt(char *str)
{
	t_prompt *prompt;

	prompt = malloc(sizeof(t_prompt));
	prompt->str = ft_strdup(str);
	prompt->size = ft_strlen(prompt->str);
	return (prompt);
}
