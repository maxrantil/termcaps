/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_shift.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 15:09:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_insertion_shift(t_term *term, char *input)
{
	int	col_cpy;

	col_cpy = term->indx;
	while (&input[col_cpy] >= &input[term->indx])
	{
		input[col_cpy] = input[col_cpy] ^ input[col_cpy + 1];
		input[col_cpy + 1] = input[col_cpy] ^ input[col_cpy + 1];
		input[col_cpy] = input[col_cpy] ^ input[col_cpy + 1];
		col_cpy--;
	}
}
