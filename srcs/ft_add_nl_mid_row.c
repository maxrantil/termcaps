/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nl_mid_row.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 16:16:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It takes a row number and a position in that row, and adds a newline 
 * character at that position
 * 
 * @param term the term structure
 * @param input the input string
 * @param row the row number where the newline character is
 * @param pos the position of the cursor in the input string
 */
void	ft_add_nl_mid_row(t_term *term, char *input, size_t row, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_arr;

	j = 0;
	i = -1;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
	while (++i <= term->total_row)
	{
		if (i == row)
			new_arr[i] = &input[pos];
		else
			new_arr[i] = term->nl_addr[j++];
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = new_arr;
}
