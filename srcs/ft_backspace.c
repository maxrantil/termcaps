/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/10 11:54:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	backpace_continue(t_term *t, size_t row, size_t len)
{
	if (!t->c_col)
	{
		t->c_col = t->ws_col;
		ft_setcursor(t->c_col, --t->c_row + t->start_row);
	}
	else
	{
		if (t->c_col == t->ws_col)
			t->c_col--;
		ft_setcursor(--t->c_col, t->c_row + t->start_row);
	}
	if (!len)
	{
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	ft_run_capability("ce");
	ft_shift_nl_addr(t, -1);
	ft_deletion_shift(t, BCK);
}

void	ft_backspace(t_term *t)
{
	size_t	row;
	size_t	len;

	if (&t->inp[t->index] == t->nl_addr[t->c_row]
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (t->index
		&& (t->inp[t->index - 1] == D_QUO || t->inp[t->index - 1] == S_QUO))
		ft_quote_decrement(t, 1);
	backpace_continue(t, row, len);
}
