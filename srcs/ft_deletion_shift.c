/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:25:31 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_deletion_shift(char *input, t_term *term, int mode)
{
	int	cur_cpy;

	cur_cpy = term->bytes;
	if (mode == BCK)
	{
		cur_cpy--;
		term->bytes = cur_cpy;
	}
	input[cur_cpy] = '\0';
	while (&input[cur_cpy] < &input[term->c_col])
	{
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
		input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
		cur_cpy++;
	}
	term->c_col--;
}
