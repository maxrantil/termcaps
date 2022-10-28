/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/27 15:31:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_deletion_shift(char *input, t_term *term, int mode)
{
	int	indx_cpy;

	if (mode == BCK)
		term->indx--;
	indx_cpy = term->indx;
	input[indx_cpy] = '\0';
	while (&input[indx_cpy] < &input[term->bytes])
	{
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy + 1] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		indx_cpy++;
	}
	term->bytes--;
}

void	delete(t_term *term, char *input) // Have not properly tested this
{
	ft_deletion_shift(input, term, DEL);
	ft_run_capability("ce");
	ft_print_trail(term, input);
	update_nl_addr(input, term, -1);
}

void	backspace(t_term *term, char *input) // THis removes input[term->indx - 1]
{
	if (term->indx && (input[term->indx - 1] == D_QUOTE || input[term->indx - 1] == S_QUOTE))
		quote_decrement(input, term);
	if (term->c_row && (&input[term->indx] == term->nl_addr[term->c_row])) // when you backspace to the most left byte of the line
	{
		term->c_row--;
		term->total_row--;
		ft_deletion_shift(input, term, BCK);
		nl_addr_reset(term, input); // Seems to be working good but now sure
		if (term->nl_addr[term->c_row + 1])
			term->c_col = (term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1]);
		else
		{
			term->c_col = (&input[term->indx] - term->nl_addr[term->c_row]);
			if (!term->total_row)
				term->c_col++;
		}
		if (!term->c_row)
			term->c_col += term->prompt_len;
		else
			term->c_col += term->m_prompt_len;
		ft_setcursor(term->c_col, term->c_row);
		ft_run_capability("cd");
		if (input[term->indx])
			ft_print_line_trail(term, input);
	}
	else
	{
		ft_setcursor(--term->c_col, term->c_row);
		ft_run_capability("ce");
		ft_deletion_shift(input, term, BCK);
		if (input[term->indx])
			ft_print_trail(term, input);
	}
	update_nl_addr(input, term, -1);
}
