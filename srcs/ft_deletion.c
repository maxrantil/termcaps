/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/03 15:45:50 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	quote_decremented(char *input, t_term *term)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = input[term->index];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == input[term->index])
	{
		term->quote = 0;
		term->q_qty--;
	}
}

void	delete(t_term *term, char *input)
{
	size_t	len;
	size_t	row;

	if (term->index
		&& (input[term->index] == D_QUO || input[term->index] == S_QUO))
		quote_decremented(input, term);
	row = row_lowest_line(term);
	if (term->nl_addr[row + 1]
		&& (&input[term->index + 1] == term->nl_addr[term->c_row + 1]
			&& is_prompt_line(term, term->c_row + 1)))
		return ;
	if (term->nl_addr[row + 1])
		len = (term->nl_addr[row + 1] - term->nl_addr[row]) - 1;
	else
		len = &input[term->bytes] - term->nl_addr[row];
	update_nl_addr_del(term);
	ft_deletion_shift(input, term, DEL);
	ft_run_capability("ce");
	if (!len)
	{
		remove_nl_addr(term, row);
		term->total_row--;
	}
}

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
		remove_nl_addr(term, row);
		term->total_row--;
	}
	ft_run_capability("ce");
	shift_nl_addr(term, -1);
	ft_deletion_shift(input, term, BCK);
}

void	backspace(t_term *term, char *input)
{
	size_t	row;
	size_t	len;

	if (&input[term->index] == term->nl_addr[term->c_row]
		&& is_prompt_line(term, term->c_row))
		return ;
	row = row_lowest_line(term);
	if (term->nl_addr[row + 1])
		len = (term->nl_addr[row + 1] - term->nl_addr[row]) - 1;
	else
		len = &input[term->bytes] - term->nl_addr[row];
	if (term->index
		&& (input[term->index - 1] == D_QUO || input[term->index - 1] == S_QUO))
		quote_decrement(input, term);
	backpace_continue(term, input, row, len);
}
