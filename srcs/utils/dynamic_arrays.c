/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 06:34:29 by niguinti          #+#    #+#             */
/*   Updated: 2020/02/02 22:04:39 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**realloc_args(char **ar, int new_size)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!(ret = ft_memalloc(sizeof(char *) * new_size)))
		return (NULL);
	while (ar[i])
	{
		ret[i] = ft_strdup(ar[i]);
		free(ar[i]);
		ar[i] = NULL;
		i++;
	}
	return (ret);
}

char	*push_args(t_node *node, char *s)
{
	char	*ret;
	char	**tmp;

	tmp = node->args;
	ret = NULL;
	if (node->cur_i == node->capacity)
	{
		if (!(node->args = realloc_args(node->args\
						, node->cur_size + ARGS_ARR_SIZE)))
			exit(0);
		free(tmp);
		node->cur_size += ARGS_ARR_SIZE;
		node->capacity = node->cur_size - 1;
	}
	if (s != NULL)
	{
		node->args[node->cur_i] = s;
		ret = node->args[node->cur_i];
		node->cur_i++;
	}
	return (ret);
}
