/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_t->inp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 16:37:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the cursor is not at the end of the line, move it one space to the right
 *
 * @param t->inp the string that is being edited
 * @param t the struct that holds all the information about the terminal
 */
static void	ft_right(t_term *t)
{
	if (t->index < t->bytes)
	{
		if (t->nl_addr[t->c_row + 1])
		{
			if (&t->inp[t->index] < (t->nl_addr[t->c_row + 1] - 1))
			{
				t->index++;
				ft_setcursor(++t->c_col, ft_display_row(t, t->c_row));
				// ft_setcursor(++t->c_col, t->c_row + t->start_row);
			}
		}
		else
		{
			t->index++;
			ft_setcursor(++t->c_col, ft_display_row(t, t->c_row));
			// ft_setcursor(++t->c_col, t->c_row + t->start_row);
		}
	}
}

/**
 * It moves the cursor left one character
 *
 * @param t->inp the string that the user is typing in
 * @param t the t_term struct
 */
// static void	ft_left(t_term *t)
// {
// 	size_t	row;

// 	// row = t->c_row + t->start_row;
// 	if (&t->inp[t->index] == t->nl_addr[t->c_row])
// 	{
// 		if (t->c_row == 1)
// 			t->c_col = t->prompt_len;
// 		else
// 			t->c_col = t->m_prompt_len;
// 		if (t->c_row > 0)
// 			t->c_col += (t->nl_addr[t->c_row] - t->nl_addr[--t->c_row]);
// 		// if (t->c_row + t->start_row > t->ws_row)
// 		// 	row = (t->ws_row - (t->total_row + 1)) + t->c_row;
// 		// else
// 		// 	row = t->c_row + t->start_row;
// 	}
// 	if (t->c_row + t->start_row >= t->ws_row - 1)
// 		row = (t->ws_row - (t->total_row + 1)) + t->c_row;
// 	else
// 		row = t->c_row + t->start_row;
// 	t->index--;
// 	ft_setcursor(--t->c_col, row);
// }
static void	ft_left(t_term *t)
{
	size_t	row;

	row = ft_get_linenbr();
	if (&t->inp[t->index] == t->nl_addr[t->c_row])
	{
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
		if (t->c_row > 0)
			t->c_col += (t->nl_addr[t->c_row] - t->nl_addr[--t->c_row]);
		row--;
	}
	// ft_setcursor(t->ws_col - 15, t->ws_row - 3);
	// ft_putnbr(t->start_row + t->c_row);
	// ft_putchar('I');
	// ft_putnbr(t->ws_row);
	// // ft_setcursor(t->c_col, t->c_row);
	// if (((t->start_row + t->c_row) + 1) >= t->ws_row)
	// 	row = t->start_row - (t->total_row - t->c_row);
	// else
	// 	row = t->c_row + t->start_row;
	t->index--;
	// ft_setcursor(--t->c_col, ft_display_row(t, t->c_row));
	ft_setcursor(--t->c_col, row);
}

void	ft_arrow_input(t_term *t)
{
	static size_t	his;

	if (t->ch == 'D' && t->index)
		ft_left(t);
	else if (t->ch == 'C')
		ft_right(t);
	else if (t->ch == 'A' && his < t->v_history.len)
		ft_history_trigger(t, ++his);
	else if (t->ch == 'B' && his > 0)
		ft_history_trigger(t, --his);
}
