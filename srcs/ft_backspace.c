/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 13:54:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	backpace_continue(t_term *term, char *input, size_t row, size_t len)
{
	if (!term->c_col)
	{
		term->c_col = term->ws_col;
		ft_setcursor(term->c_col, --term->c_row);
	}
	else
	{
		if (term->c_col == term->ws_col)
			term->c_col--;
		ft_setcursor(--term->c_col, term->c_row);
	}
	if (!len)
	{
		ft_remove_nl_addr(term, row);
		term->total_row--;
	}
	ft_run_capability("ce");
	ft_shift_nl_addr(term, -1);
	ft_deletion_shift(input, term, BCK);
}

void	ft_backspace(t_term *term, char *input)
{
	size_t	row;
	size_t	len;

	if (&input[term->index] == term->nl_addr[term->c_row]
		&& ft_is_prompt_line(term, term->c_row))
		return ;
	row = ft_row_lowest_line(term);
	if (term->nl_addr[row + 1])
		len = (term->nl_addr[row + 1] - term->nl_addr[row]) - 1;
	else
		len = &input[term->bytes] - term->nl_addr[row];
	if (term->index
		&& (input[term->index - 1] == D_QUO || input[term->index - 1] == S_QUO))
		ft_quote_decrement(input, term, 1);
	backpace_continue(term, input, row, len);
}
