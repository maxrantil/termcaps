/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_row.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:42:10 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 13:03:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

size_t	ft_display_row(t_term *t, size_t c_row)
{
	size_t	row;

	row = 0;
	// if (t->start_row == t->ws_row) // This works for creating new_lines
	// if (((t->start_row + c_row) + 1) >= t->ws_row) // THis works for cursor movement
	// 	row = t->start_row - (t->total_row - c_row);
	if ((t->start_row + c_row) > t->ws_row) // THis works for cursor movement
		row = t->start_row - (t->total_row - c_row);
	else
		row = c_row + t->start_row;
	return (row);
}

size_t	ft_display_row_v2(t_term *t, size_t c_row)
{
	size_t	row;

	row = 0;
	// if (t->start_row == t->ws_row) // This works for creating new_lines
	if ((t->start_row + c_row) > t->ws_row) // THis works for cursor movement
		row = t->ws_row;
	else
		row = c_row + t->start_row;
	return (row);
}
