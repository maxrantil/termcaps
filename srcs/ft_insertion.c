/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/01 15:09:10 by mbarutel         ###   ########.fr       */
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

// void	insertion(t_term *term, char *input)
// {
// 	size_t indx_cpy;
	
// 	ft_putc(term->ch);
// 	if (input[term->indx])
// 		ft_insertion_shift(term, input);
// 	term->bytes++;
// 	input[term->indx++] = term->ch;
// 	ft_setcursor(++term->c_col, term->c_row);
// 	/*
// 		if no line_below
// 			line = c_col + (input[indx] - input[bytes]);
// 		else
// 			line = c_col + (input[indx] - &nl_addr[c_row + 1][-1]); // this is wrong
// 		if line == ws_col
// 		{
// 			IF NO line below
// 			{
// 				if c_row == ws_col
// 				{
// 					c_row++;
// 					c_col = 0;
// 					setcursur
// 				}
// 				total_row++;
// 				get_nl_addr(term, input, index); // index for location
// 			}
// 			if there is a line below
// 			{
// 				if c_row == ws_col
// 				{
// 					c_row++;
// 					c_col = 0;
// 					setcursur
// 				}
// 				total_row++;
// 				middle_nl_addr(term, input, index); // index for location
// 			}
// 		}
// 	*/







	
// 	/*				For cursor in not at the end and c_row == total_row				*/
// 	if (!term->nl_addr[term->c_row + 1])
// 	{
// 		if ((term->c_col != term->ws_col) && (term->c_col + (&input[term->bytes] - &input[term->indx]) == term->ws_col))
// 		{
// 			term->total_row++;
// 			indx_cpy = term->indx;
// 			term->indx = term->bytes;
// 			insert_middle_nl_addr(term, input, term->c_row + 1);
// 			term->indx = indx_cpy;
// 			ft_print_trail(term, input);
// 		}
// 	}
// 	/*									Testing										*/
// 	if (term->nl_addr[term->c_row + 1])
// 	{	
// 		// update_nl_addr(input, term, 1);
// 		if (term->nl_addr[term->c_row + 1][-1] == '\n' || term->nl_addr[term->c_row + 1][-1] == '\\')
// 		{
// 			if ((term->c_col != term->ws_col) && (term->c_col + (term->nl_addr[term->c_row + 1] - &input[term->indx]) == term->ws_col + 1)) // This is for catching when cursur inside text and end of line with \ or \n reaches end of terminal
// 			{
// 				term->total_row++;
// 				indx_cpy = term->indx;
// 				term->indx = (term->nl_addr[term->c_row + 1] - term->nl_addr[0]) - 1;
// 				insert_middle_nl_addr(term, input, term->c_row + 1); // I reckon this is not right
// 				term->indx = indx_cpy;
// 				ft_print_trail(term, input);
// 			}
// 		}
// 	}
// 	if ((term->c_col != term->ws_col) && (&input[term->bytes] - term->nl_addr[term->total_row]) == (long)(term->ws_col)) // This is for catching the text len on the last row exceeding the terminal size
// 	{
// 		term->total_row++;
// 		indx_cpy = term->indx;
// 		term->indx = term->bytes;
// 		get_nl_addr(term, input);
// 		term->indx = indx_cpy;
// 	}
// 	// if ((term->c_col != term->ws_col)) // This is for catching the text len on the last row exceeding the terminal size
// 	// {
// 	// 	if ((&input[term->bytes] - term->nl_addr[term->total_row]) == (long)(term->ws_col))
// 	// 	{
// 	// 		term->total_row++;
// 	// 		indx_cpy = term->indx;
// 	// 		term->indx = term->bytes;
// 	// 		get_nl_addr(term, input);
// 	// 		term->indx = indx_cpy;
// 	// 	}
// 	// 	if (term->nl_addr[term->c_row + 1] && is_prompt_line(term, 1) &&  (term->c_col + ((term->nl_addr[term->c_row + 1] - &input[term->indx])) == term->ws_col))
// 	// 	{
// 	// 		term->total_row++;
// 	// 		term->c_row++;
// 	// 		insert_middle_nl_addr(term, input);
// 	// 		term->c_row--;
// 	// 		term->c_col = 0;
// 	// 		ft_setcursor(term->c_col, term->c_row);
// 	// 		// return ;
// 	// 		// // write(1, &input[term->indx], ((term->nl_addr[term->c_row + 1] - &input[term->indx])));
// 	// 		// write(1, &input[term->indx], ((&input[term->indx] - term->nl_addr[term->c_row])));
// 	// 		// ft_run_capability("cd");
// 	// 		// ft_setcursor(0, term->c_row + 1);
// 	// 		// ft_putstr(MINI_PROMPT);
// 	// 		// ft_putstr(term->nl_addr[term->c_row + 1]);
// 	// 	}
// 	// }
// 	// // if ((term->c_col != term->ws_col) && (&input[term->bytes] - term->nl_addr[term->total_row]) == (long)(term->ws_col)) // This is for catching the text len on the last row exceeding the terminal size
// 	// // {
// 	// // 	term->total_row++;
// 	// // 	indx_cpy = term->indx;
// 	// // 	term->indx = term->bytes;
// 	// // 	get_nl_addr(term, input);
// 	// // 	term->indx = indx_cpy;
// 	// // }
// 	// // if (term->nl_addr[term->c_row + 1] && (term->c_col != term->ws_col) && (term->nl_addr[term->c_row + 1][-1] == '\n' || term->nl_addr[term->c_row + 1][-1] == '\\'))
// 	// // {
// 	// // 	if (term->c_col + term->nl_addr[term->c_row + 1] - &input[term->indx] >= (long)term->ws_col)
// 	// 	{
// 	// 		term->total_row++;
// 	// 		insert_middle_nl_addr(term, input);
// 	// 		ft_setcursor(0, term->c_row + 1);
// 	// 		ft_run_capability("cd");
// 	// 		int b;
			
// 	// 		b = term->c_row + 1;
// 	// 		while (term->nl_addr[b])
// 	// 		{
// 	// 			if (term->nl_addr[b][-1] == '\n' || term->nl_addr[b][-1] == '\\')
// 	// 				write(1, MINI_PROMPT, term->m_prompt_len);
// 	// 			if (term->nl_addr[b + 1])
// 	// 				write(1, term->nl_addr[b], term->nl_addr[b + 1] - term->nl_addr[b]);
// 	// 			else
// 	// 				write(1, term->nl_addr[b], &input[term->bytes] - term->nl_addr[b]);
// 	// 			b++;
// 	// 		}
// 	// 		ft_setcursor(term->c_col, term->c_row);
// 	// 	}
// 	// }
// 	if (term->c_col == (term->ws_col)) // -> This is new. Maybe no need for print trail inside nl_terminal_size()	
// 		nl_terminal_size(term, input);
// 	if (input[term->indx])
// 		ft_print_trail(term, input);
// 	if (term->ch == ENTER && (term->q_qty % 2) && input[term->indx - 2] != '\\')
// 		nl_open_qoute(term, input);

// 	/*
// 		print line at the end, starting from indx to downwards
// 	*/
// }

static void	nl_addr_increment(t_term *term) // I think this is okay
{
	size_t row;
	
	row = term->c_row;
	while (term->nl_addr[row + 1] && is_prompt_line(term, row + 1))
	{
		term->nl_addr[row + 1] = &term->nl_addr[row + 1][1];
		row++;
	}
}

// static void	nl_addr_decrement(t_term *term) // I think this is okay
// {
// 	size_t row;
	
// 	row = term->c_row;
// 	while (term->nl_addr[row + 1] && !is_prompt_line(term, row + 1))
// 	{
// 		term->nl_addr[row + 1] = &term->nl_addr[row + 1][-1];
// 		row++;
// 	}
// }

static void nl_create_check(t_term *term, char *input)
{
	size_t row;
	size_t len;

	row = term->c_row;
	while (term->nl_addr[row + 1] && !is_prompt_line(term, row + 1))
		row++;
	// ft_setcursor(0, term->ws_row - 3);
	// ft_putnbr(row);
	// ft_setcursor(term->c_col, term->c_row);
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
	// ft_setcursor(0, term->ws_row - 2);
	// ft_putnbr(len);
	// ft_putchar('|');
	// ft_putnbr(term->ws_col);
	// ft_setcursor(term->c_col, term->c_row);
	if (len == term->ws_col)
	{
		// ft_setcursor(0, term->ws_row - 2);
		// ft_putstr("CAR");
		// ft_setcursor(term->c_col, term->c_row);
		term->total_row++;
		if (term->nl_addr[row + 1])
			insert_middle_nl_addr(term, input, row + 1, (size_t)(&term->nl_addr[row + 1][-1] - term->nl_addr[0]));
		else
		{
			ft_setcursor(0, term->ws_row - 2);
			ft_putstr("CAR");
			ft_setcursor(term->c_col, term->c_row);
			get_nl_addr(term, input, term->bytes);
		}
	}
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
	while (term->nl_addr[row])
	{
		if (is_prompt_line(term, row))
			term->nl_addr[row] = &term->nl_addr[row][1];
		row++;
	}
}

void	insertion(t_term *term, char *input)
{
	size_t indx_cpy;
	
	if (term->c_col != term->ws_col)
		ft_putc(term->ch);
	ft_setcursor(++term->c_col, term->c_row);
	ft_nl_addr_update(term);
	if (input[term->indx])
		ft_insertion_shift(term, input);
	term->bytes++;
	input[term->indx++] = term->ch;
	nl_create_check(term, input);
	// ft_run_capability("cd");
	if (input[term->indx])
		ft_print_trail(term, input);
	if (term->ch == ENTER && (term->q_qty % 2) && input[term->indx - 2] != '\\')
		nl_open_qoute(term, input);
}
