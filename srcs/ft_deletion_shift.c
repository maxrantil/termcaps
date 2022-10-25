/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 15:05:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_deletion_shift(char *input, t_term *term, int mode)
{
	int	indx_cpy;

	if (mode == BCK)
		term->indx--;
	indx_cpy = term->indx;
	input[indx_cpy] = '\0';
	while (&input[indx_cpy] < &input[term->bytes])
	{
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy + 1] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		indx_cpy++;
	}
	term->bytes--;
}
