/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/11 13:58:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_shift_insert(t_term *t)
{
	int	bytes_cpy;

	bytes_cpy = t->bytes;
	while (&t->inp[bytes_cpy] >= &t->inp[t->index])
	{
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy + 1] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		bytes_cpy--;
	}
}

static size_t	ft_len_lowest_line(t_term *t, size_t row)
{
	size_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row];
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (ft_is_prompt_line(t, row))
	{
		if (!row)
			len += t->prompt_len;
		else
			len += t->m_prompt_len;
	}
	return (len);
}

static void	ft_trigger_nl(t_term *t)
{
	size_t	len;
	size_t	row;

	row = ft_row_lowest_line(t);
	len = ft_len_lowest_line(t, row);
	if (len == t->ws_col)
	{
		t->total_row++;
		ft_add_nl_last_row(t, t->bytes);
	}
	if (len == t->ws_col + 1)
		if (t->nl_addr[row + 1])
			ft_add_nl_mid_row(t, row + 1, (size_t)(&t->nl_addr[row + 1][-1] - t->nl_addr[0]));
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		ft_putchar('\n');
		ft_setcursor(t->c_col, ft_get_linenbr());
	}
}

void	ft_insertion(t_term *t)
{
	if (t->ch == ENTER)
	{
		if (!t->nl_addr[t->c_row + 1])
		{
			if (t->inp[t->bytes - 1] == '\\' || t->q_qty % 2)
			{
				t->inp[t->bytes++] = t->ch;
				ft_create_prompt_line(t, t->bytes);
				t->index = t->bytes;
			}
		}
	}
	else
	{
		ft_putc(t->ch);
		if (t->ch == D_QUO || t->ch == S_QUO)
			if (!t->index || t->inp[t->index - 1] != '\\')
				ft_quote_handling(t, t->ch);
		if (t->c_col == t->ws_col)
		{
			t->c_col = 0;
			ft_setcursor(t->c_col, ft_get_linenbr() + 1);
		}
		else
			ft_setcursor(++t->c_col, ft_get_linenbr());
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = t->ch;
		if (t->inp[t->index])
			ft_print_trail(t);
		t->bytes++;
	}
	ft_trigger_nl(t);
}
