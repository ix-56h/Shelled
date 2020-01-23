/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niguinti <0x00fi@protonmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:17:19 by niguinti          #+#    #+#             */
/*   Updated: 2020/01/23 23:24:17 by niguinti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	expand_tilde()
{
	//get the home directory and replace the ~ with the directory in the word
}

void	expand_word()
{
	char	*word;

	// step 1
	if (word[i] == '~')
		expand_tilde();
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
