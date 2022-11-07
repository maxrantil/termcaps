/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_row_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 15:18:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It returns the row number of the lowest line in the terminal
 * 
 * @param term the terminal structure
 * 
 * @return The row number of the lowest line in the terminal.
 */
size_t	ft_row_lowest_line(t_term *term)
{
	size_t	row;

	row = term->c_row;
	while (term->nl_addr[row + 1] && !ft_is_prompt_line(term, row + 1))
		row++;
	return (row);
}
