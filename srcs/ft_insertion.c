/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/27 20:28:09 by mbarutel         ###   ########.fr       */
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

void	insertion(t_term *term, char *input)
{
	ft_putc(term->ch);
	update_nl_addr(input, term, 1);
	if (input[term->indx])
		ft_insertion_shift(term, input);
	input[term->indx++] = term->ch;
	ft_setcursor(++term->c_col, term->c_row);
	// if (input[term->indx] && (input[term->indx + 1] != '\n' && input[term->indx + 1] != '\\'))
	// 	ft_print_trail(term, input);
	term->bytes++;
	if (term->c_col == (term->ws_col)) // -> This is new. Maybe no need for print trail inside nl_terminal_size()
		nl_terminal_size(term, input);
	if (input[term->indx])
		ft_print_trail(term, input);
	if (term->ch == ENTER && (term->q_qty % 2))
		nl_open_qoute(term, input);
}
