/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 09:46:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It deletes a character from the term->inp string and shifts the rest of the 
 * string to the left
 * 
 * @param term->inp the string that is being edited
 * @param term the structure that contains the terminal's information
 * @param mode 0 for deletion, 1 for backspace
 */
void	ft_deletion_shift(t_term *term, int mode)
{
	int	index_cpy;

	if (mode == BCK)
		term->index--;
	index_cpy = term->index;
	term->inp[index_cpy] = '\0';
	while (&term->inp[index_cpy] < &term->inp[term->bytes])
	{
		term->inp[index_cpy] = term->inp[index_cpy] ^ term->inp[index_cpy + 1];
		term->inp[index_cpy + 1] = term->inp[index_cpy] ^ term->inp[index_cpy + 1];
		term->inp[index_cpy] = term->inp[index_cpy] ^ term->inp[index_cpy + 1];
		index_cpy++;
	}
	term->bytes--;
}
