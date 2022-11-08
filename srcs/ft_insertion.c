/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 14:43:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It shifts the characters in the input string to the right, starting at the 
 * current index, and ending at the end of the string
 * 
 * @param term a pointer to the t_term struct
 * @param input the string that is being edited
 */
static void	ft_shift_insert(t_term *term, char *input)
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

/**
 * It returns the length of the lowest line in the terminal
 * 
 * @param term the terminal structure
 * @param input the string of characters that the user has typed in
 * @param row the row of the cursor
 * 
 * @return The length of the lowest line.
 */
static size_t	ft_len_lowest_line(t_term *term, char *input, size_t row)
{
	size_t	len;

	if (term->nl_addr[row + 1])
		len = term->nl_addr[row + 1] - term->nl_addr[row];
	else
		len = &input[term->bytes] - term->nl_addr[row];
	if (ft_is_prompt_line(term, row))
	{
		if (!row)
			len += term->prompt_len;
		else
			len += term->m_prompt_len;
	}
	return (len);
}

/**
 * It adds a newline to the
 * input string, and updates the cursor position
 * 
 * @param term the term struct
 * @param input the input string
 */
static void	ft_trigger_nl(t_term *term, char *input)
{
	size_t	len;
	size_t	row;

	row = ft_row_lowest_line(term);
	len = ft_len_lowest_line(term, input, row);
	if (len == term->ws_col)
	{
		term->total_row++;
		ft_add_nl_last_row(term, input, term->bytes);
	}
	if (len == term->ws_col + 1)
		if (term->nl_addr[row + 1])
			ft_add_nl_mid_row(term, input, row + 1,
				(size_t)(&term->nl_addr[row + 1][-1] - term->nl_addr[0]));
	if (term->c_col == term->ws_col)
	{
		term->c_col = 0;
		ft_setcursor(term->c_col, ++term->c_row);
	}
}


/**
 * It handles the insertion of characters into the input buffer
 * 
 * @param term the term structure
 * @param input the string that is being edited
 */
void	ft_insertion(t_term *term, char *input)
{
	if (term->ch == ENTER)
	{
		if (!term->nl_addr[term->c_row + 1])
		{
			if (input[term->bytes - 1] == '\\' || term->q_qty % 2)
			{
				input[term->bytes++] = term->ch;
				ft_create_prompt_line(term, input, term->bytes);
				term->index = term->bytes;
			}
		}
		/* else
		{
			if (term->q_qty % 2)
			{
				term->index = term->nl_addr[term->c_row + 1] - &input[0];
				ft_shift_insert(term, input);
				input[term->index] = term->ch;
				ft_create_prompt_line(term, input, --term->index);
			}
		} */
	}
	else
	{
		ft_putc(term->ch);
		if (term->ch == D_QUO || term->ch == S_QUO)
			if (!term->index || input[term->index - 1] != '\\')
				ft_quote_handling(term, term->ch);
		ft_setcursor(++term->c_col, term->c_row);
		ft_shift_nl_addr(term, 1);
		if (input[term->index])
			ft_shift_insert(term, input);
		input[term->index++] = term->ch;
		term->bytes++;
	}
	ft_trigger_nl(term, input);
}
