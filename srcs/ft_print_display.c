/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/27 20:16:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void ft_print_line_trail(t_term *term, char *input)
{
	int		j;
	size_t	i;
	
	i = term->c_row;
	ft_run_capability("vi");
	while (i <= term->total_row)
	{
		if (term->m_prompt_len && i < term->total_row)
			ft_putstr(MINI_PROMPT);
		j = term->indx;
		if (term->nl_addr[i + 1])
		{
			while (&input[j] < term->nl_addr[i + 1])
				write(1, &input[j++], 1);
		}
		else
			while (&input[j] < &input[term->bytes])
				write(1, &input[j++], 1);
		i++;
	}
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
	
}

static void print_line_trail(t_term *term, char *input)
{
	// int index_cpy;

	// index_cpy = term->indx;
	if (term->nl_addr[term->c_row + 1])
	{
		// if (((term->nl_addr[term->c_row + 1] - &input[term->indx]) + term->c_col) < term->ws_col)
		// {
		update_nl_addr(input, term, -1);
		ft_run_capability("cd");
		write(1, &input[term->indx], (&input[term->bytes] - &input[term->indx]));
			// if ((&input[term->bytes] - &input[term->indx]) + term->c_col > term->ws_col)
			// {
			// 	term->total_row++;
			// 	term->indx += (term->ws_col - term->c_col) + 1;
			// 	get_nl_addr(term, input);
			// 	term->indx = index_cpy;
			// }
	}
	else
		write(1, &input[term->indx], &input[term->bytes] - &input[term->indx]);
}

void	ft_print_trail(t_term *term, char *input)
{
	ft_run_capability("vi");
	print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
