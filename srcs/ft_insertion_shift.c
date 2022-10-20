/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_shift.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 16:25:31 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_insertion_shift(t_term *term, char *input)
{
	int	bytes_cpy;

	bytes_cpy = term->bytes;
	while (&input[bytes_cpy] >= &input[term->c_col])
	{
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy + 1] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		bytes_cpy--;
	}
}
