/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 13:55:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It deletes a character from the input string and shifts the rest of the 
 * string to the left
 * 
 * @param input the string that is being edited
 * @param term the structure that contains the terminal's information
 * @param mode 0 for deletion, 1 for backspace
 */
void	ft_deletion_shift(char *input, t_term *term, int mode)
{
	int	index_cpy;

	if (mode == BCK)
		term->index--;
	index_cpy = term->index;
	input[index_cpy] = '\0';
	while (&input[index_cpy] < &input[term->bytes])
	{
		input[index_cpy] = input[index_cpy] ^ input[index_cpy + 1];
		input[index_cpy + 1] = input[index_cpy] ^ input[index_cpy + 1];
		input[index_cpy] = input[index_cpy] ^ input[index_cpy + 1];
		index_cpy++;
	}
	term->bytes--;
}
