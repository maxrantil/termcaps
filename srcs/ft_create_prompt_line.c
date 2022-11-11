/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 12:55:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

// size_t	ft_display_row((t_term *t, size_t c_row)
// {
// 	size_t	row;

// 	row = 0;
// 	if (t->start_row == t->ws_row) // This works for creating new_lines
// 		row = t->start_row - (t->total_row - c_row);
// 	else
// 		row = c_row + t->start_row;
// 	return (row);
// }

void	ft_create_prompt_line(t_term *t, size_t loc)
{
	t->c_row++;
	t->total_row++;
	t->c_col = t->m_prompt_len;
	ft_putchar('\n');
	// ft_setcursor(0, ft_display_row(t, t->c_row));
	ft_setcursor(0, ft_display_row_v2(t, t->c_row));
	write(1, MINI_PROMPT, t->m_prompt_len);
	// if (t->nl_addr[t->c_row])
	// 	ft_add_nl_mid_row(t, t->c_row, loc);
	// else
	ft_add_nl_last_row(t, loc);
}
