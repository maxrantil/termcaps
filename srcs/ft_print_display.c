/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/01 15:45:05 by mbarutel         ###   ########.fr       */
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

// static void print_line_trail(t_term *term, char *input)
// {
// 	// if (term->nl_addr[term->c_row + 1] && is_prompt_line(term, term->c_row + 1))
// 	if (term->nl_addr[term->c_row + 1])
// 	{
// 		write(1, &input[term->indx], ((term->nl_addr[term->c_row + 1] - &input[term->indx])));
// 	}
// 	else
// 	{
// 		ft_run_capability("cd");
// 		write(1, &input[term->indx], (&input[term->bytes] - &input[term->indx]));
// 	}
// }
static void print_line_trail(t_term *term, char *input) // something wrong here
{
	size_t row;
	
	row = term->c_row;
	ft_setcursor(0, row);
	ft_run_capability("cd");
	while (row <= term->total_row)
	{
		if (is_prompt_line(term, row))
		{
			if (!row)
				ft_putstr(PROMPT);
			else
				ft_putstr(MINI_PROMPT);
		}
		if (term->nl_addr[row + 1])
			write(1, term->nl_addr[row], term->nl_addr[row + 1] - term->nl_addr[row]);
		else
			write(1, term->nl_addr[row], &input[term->bytes] - term->nl_addr[row]);
		ft_setcursor(0, ++row);
	}
}
// static void print_line_trail(t_term *term, char *input)
// {
// 	size_t row;
	
// 	row = term->c_row;
// 	ft_run_capability("cd");
// 	ft_setcursor(0, row);
// 	while (term->nl_addr[row + 1])
// 	{
// 		if (is_prompt_line(term, row))
// 		{
// 			if (!term->c_row)
// 				ft_putstr(PROMPT);
// 			else
// 				ft_putstr(MINI_PROMPT);
// 		}
// 		write(1, term->nl_addr[row], term->nl_addr[row + 1] - term->nl_addr[row]);
// 		ft_setcursor(0, ++row);
// 	}
// 	write(1, term->nl_addr[row], &input[term->bytes] - term->nl_addr[row]);
// }

void	ft_print_trail(t_term *term, char *input)
{
	ft_run_capability("vi");
	print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
