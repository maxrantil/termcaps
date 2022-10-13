/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifting_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 14:51:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	insertion_shift(char *input, int *bytes, int cur)
{
	int	bytes_cpy;

	bytes_cpy = *bytes;
	while (&input[bytes_cpy] >= &input[cur])
	{
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy + 1] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		bytes_cpy--;
	}
}

void	deletion_shift(char *input, int *bytes, int *cur, int mode)
{
	int	cur_cpy;

	cur_cpy = *cur;
	if (mode == BCK)
	{
		cur_cpy--;
		*cur = cur_cpy;
	}
	input[cur_cpy] = '\0';
	while (&input[cur_cpy] < &input[*bytes])
	{
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		cur_cpy++;
	}
	bytes[0]--;
}
