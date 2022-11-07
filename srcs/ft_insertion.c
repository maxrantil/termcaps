/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 11:15:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	shift_insert(t_term *term, char *input)
{
	int	bytes_cpy;

	bytes_cpy = term->bytes;
	while (&input[bytes_cpy] >= &input[term->index])
	{
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy + 1] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		bytes_cpy--;
	}
}

size_t	len_lowest_line(t_term *term, char *input, size_t row)
{
	size_t	len;

	if (term->nl_addr[row + 1])
		len = term->nl_addr[row + 1] - term->nl_addr[row];
	else
		len = &input[term->bytes] - term->nl_addr[row];
	if (is_prompt_line(term, row))
	{
		if (!row)
			len += term->prompt_len;
		else
			len += term->m_prompt_len;
	}
	return (len);
}

static void	trigger_nl(t_term *term, char *input)
{
	size_t	len;
	size_t	row;

	row = row_lowest_line(term);
	len = len_lowest_line(term, input, row);
	if (len == term->ws_col)
	{
		term->total_row++;
		add_nl_last_row(term, input, term->bytes);
	}
	if (len == term->ws_col + 1)
		if (term->nl_addr[row + 1])
			add_nl_mid_row(term, input, row + 1,
				(size_t)(&term->nl_addr[row + 1][-1] - term->nl_addr[0]));
	if (term->c_col == term->ws_col)
	{
		term->c_col = 0;
		ft_setcursor(term->c_col, ++term->c_row);
	}
}

void	shift_nl_addr(t_term *term, int num)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->nl_addr[row] && !is_prompt_line(term, row))
		row++;
	while (term->nl_addr[row++])
		term->nl_addr[row - 1] = &term->nl_addr[row - 1][num];
}

void	insertion(t_term *term, char *input)
{
	ft_putc(term->ch);
	if (term->ch == D_QUO || term->ch == S_QUO)
		if (!term->index || input[term->index - 1] != '\\')
			quote_handling(term, term->ch);
	ft_setcursor(++term->c_col, term->c_row);
	shift_nl_addr(term, 1);
	if (input[term->index])
		shift_insert(term, input);
	input[term->index++] = term->ch;
	term->bytes++;
	trigger_nl(term, input);
}
