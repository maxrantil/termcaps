/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_shift.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 15:19:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_insertion_shift(t_term *term, char *input)
{
	int	indx_cpy;

	indx_cpy = term->indx;
	while (&input[indx_cpy] >= &input[term->c_col])
	{
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy + 1] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		indx_cpy--;
	}
}
