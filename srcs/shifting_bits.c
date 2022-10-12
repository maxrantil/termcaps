/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifting_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/12 09:45:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	insertion_shift(char *input, int *i, int cur)
{
	int	i_cpy;

	i_cpy = *i;
	while (&input[i_cpy] >= &input[cur])
	{
		input[i_cpy] = input[i_cpy] ^ input[i_cpy + 1];
		input[i_cpy + 1] = input[i_cpy] ^ input[i_cpy + 1];
		input[i_cpy] = input[i_cpy] ^ input[i_cpy + 1];
		i_cpy--;
	}
}

void	deletion_shift(char *input, int *i, int *cur, int mode)
{
	int	cur_cpy;

	cur_cpy = *cur;
	if (mode == BCK)
	{
		cur_cpy--;
		*cur = cur_cpy;
	}
	input[cur_cpy] = '\0';
	while (&input[cur_cpy] < &input[*i])
	{
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		cur_cpy++;
	}
	i[0]--;
}
