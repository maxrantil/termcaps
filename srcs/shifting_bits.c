/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifting_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 13:37:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	insertion_shift(t_term *term, char *input)
{
	int	col_cpy;

	col_cpy = term->col;
	while (&input[col_cpy] >= &input[term->cursor])
	{
		input[col_cpy] = input[col_cpy] ^ input[col_cpy + 1];
		input[col_cpy + 1] = input[col_cpy] ^ input[col_cpy + 1];
		input[col_cpy] = input[col_cpy] ^ input[col_cpy + 1];
		col_cpy--;
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
	while (&input[cur_cpy] < &input[term->col])
	{
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		cur_cpy++;
	}
	term->col--;
}
