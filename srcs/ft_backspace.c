/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:36:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It scrolls the terminal up one line
 *
 * @param t the term structure
 */
static void	ft_scroll_up(t_term *t)
{
	ssize_t	row;

	row = ft_get_linenbr() + 1;
	ft_run_capability("ho");
	ft_run_capability("sr");
	ft_setcursor(t->c_col, row);
}

/*
 * It handles the backspace key
 * when the cursor is not at the beginning of the line
 *
 * @param t the term structure
 * @param row the row of the cursor
 * @param len the length of the line that is being deleted
 */
static void	backpace_continue(t_term *t, ssize_t row, ssize_t len)
{
	if (!t->c_col)
	{
		t->c_col = t->ws_col - 1;
		t->c_row--;
		ft_setcursor(t->c_col, ft_get_linenbr() - 1);
	}
	else
	{
		ft_run_capability("le");
		t->c_col--;
	}
	if (!len)
	{
		if (((t->start_row + t->c_row) + 1) >= t->ws_row)
			ft_scroll_up(t);
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	ft_run_capability("ce");
	ft_shift_nl_addr(t, -1);
	ft_deletion_shift(t, BCK);
}

/*
 * It deletes the character
 * before the cursor
 *
 * @param t the term structure
 */
void	ft_backspace(t_term *t)
{
	ssize_t	row;
	ssize_t	len;

	if (&t->inp[t->index] == t->nl_addr[t->c_row] && \
		ft_is_prompt_line(t, t->c_row))
		return ;
	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (t->index && (t->inp[t->index - 1] == D_QUO || \
		t->inp[t->index - 1] == S_QUO))
		ft_quote_decrement(t, 1);
	backpace_continue(t, row, len);
	if (t->inp[t->index])
		ft_print_trail(t);
}
