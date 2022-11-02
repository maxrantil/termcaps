/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/02 11:03:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_insertion_shift(t_term *term, char *input)
{
	int	bytes_cpy;

	bytes_cpy = term->bytes;
	while (&input[bytes_cpy] >= &input[term->indx])
	{
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy + 1] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		input[bytes_cpy] = input[bytes_cpy] ^ input[bytes_cpy + 1];
		bytes_cpy--;
	}
}

static void nl_create_check(t_term *term, char *input)
{
	size_t row;
	size_t len;

	row = term->c_row;
	while (term->nl_addr[row + 1] && !is_prompt_line(term, row + 1))
		row++;
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
	if (len == term->ws_col)
	{
		// ft_setcursor(0, term->ws_row - 2);
		// ft_putstr("CAR");
		// ft_setcursor(term->c_col, term->c_row);
		term->total_row++;
		get_nl_addr(term, input, term->bytes);
	}
	if (len == term->ws_col + 1)
		if (term->nl_addr[row + 1])
			insert_middle_nl_addr(term, input, row + 1, (size_t)(&term->nl_addr[row + 1][-1] - term->nl_addr[0]));
	if (term->c_col == term->ws_col)
	{
		term->c_col = 0;
		ft_setcursor(term->c_col, ++term->c_row);
	}
}

static void ft_nl_addr_update(t_term *term)
{
	size_t row;

	row = term->c_row + 1;
	while (term->nl_addr[row] && !is_prompt_line(term, row))
		row++;
	while (term->nl_addr[row++])
		term->nl_addr[row - 1] = &term->nl_addr[row - 1][1];
}

void	insertion(t_term *term, char *input)
{
	ft_putc(term->ch);
	ft_setcursor(++term->c_col, term->c_row);	
	ft_nl_addr_update(term);
	if (input[term->indx])
		ft_insertion_shift(term, input);
	input[term->indx++] = term->ch;
	term->bytes++;
	nl_create_check(term, input);
	if (input[term->indx])
		ft_print_trail(term, input);
	if (term->ch == ENTER && (term->q_qty % 2) && input[term->indx - 2] != '\\')
		nl_open_qoute(term, input);
}
