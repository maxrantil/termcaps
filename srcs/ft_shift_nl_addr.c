/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift_nl_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:17:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 15:19:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It shifts the newline addresses
 * in the `nl_addr` array by `num` characters
 * 
 * @param term the terminal structure
 * @param num the number of characters to shift the addresses by
 */
void	ft_shift_nl_addr(t_term *term, int num)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->nl_addr[row] && !ft_is_prompt_line(term, row))
		row++;
	while (term->nl_addr[row++])
		term->nl_addr[row - 1] = &term->nl_addr[row - 1][num];
}
