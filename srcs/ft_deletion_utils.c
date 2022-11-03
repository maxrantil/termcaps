/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 15:30:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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

size_t	row_lowest_line(t_term *term)
{
	size_t	row;

	row = term->c_row;
	while (term->nl_addr[row + 1] && !is_prompt_line(term, row + 1))
		row++;
	return (row);
}
