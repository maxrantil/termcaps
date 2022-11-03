/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/03 09:31:56 by mbarutel         ###   ########.fr       */
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

static void print_line_trail(t_term *term, char *input) // something wrong here
{
	size_t 		row;
	char		*nl_begin;
	
	nl_begin = NULL;
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
		nl_begin = term->nl_addr[row];
		if (*nl_begin == '\n')
			nl_begin++;
		if (term->nl_addr[row + 1])
			write(1, nl_begin, term->nl_addr[row + 1] - nl_begin);
		else
			write(1, nl_begin, &input[term->bytes] - nl_begin);
		// if (term->nl_addr[row + 1])
		// 	write(1, term->nl_addr[row], term->nl_addr[row + 1] - term->nl_addr[row]);
		// else
		// 	write(1, term->nl_addr[row], &input[term->bytes] - term->nl_addr[row]);
		ft_setcursor(0, ++row);
	}
}

void	ft_print_trail(t_term *term, char *input)
{
	ft_run_capability("vi");
	print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
