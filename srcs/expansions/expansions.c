/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:17:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/25 02:45:35 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*expand_tilde(char *w,int *i)
{
	int	a;

	a = *i;
	if (w[a] == '/')
	{
		// get the home directory and replace the ~ with the path in the word
		// *i += len(home_path)
		// return new word
		return (w);
	}
	// else, return old word
	(*i)++;
	return (w);
}

void	expand_word()
{
	char	*word;
	int		i;

	i = 0;
	// step 1
	if (word[i] == '~')
		expand_tilde(word, &i);
	//expand_parameter();
	//expand_substitution();
	//expand_arithmetic();
	
	//step 2
	//field splitting ?
	//ignore step3
	//step 4
	//quote_removal();
}

void	process_expansions(void) // why not send a linked list only with words nodes
{
	// fetch nodes and applie expand_word() on each of them and substrings in char **av of the node 
}
