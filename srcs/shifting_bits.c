/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifting_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:39:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	insertion_shift(char *input, t_term *term)
{
	int	bytes_cpy;

	bytes_cpy = term->bytes;
	while (&input[bytes_cpy] >= &input[term->cursor])
	{
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy + 1] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		bytes_cpy--;
	}
}

void	deletion_shift(char *input, t_term *term, int mode)
{
	int	cur_cpy;

	cur_cpy = term->cursor;
	if (mode == BCK)
	{
		cur_cpy--;
		term->cursor = cur_cpy;
	}
	input[cur_cpy] = '\0';
	while (&input[cur_cpy] < &input[term->bytes])
	{
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		cur_cpy++;
	}
	term->bytes--;
}
