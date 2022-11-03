/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/03 16:18:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	print_prompt(size_t row)
{
	if (!row)
		ft_putstr(PROMPT);
	else
		ft_putstr(MINI_PROMPT);
}

static void	print_line_trail(t_term *term, char *input)
{
	size_t	row;
	char	*new_line;

	new_line = NULL;
	row = term->c_row;
	ft_setcursor(0, row);
	ft_run_capability("cd");
	while (row <= term->total_row)
	{
		if (is_prompt_line(term, row))
			print_prompt(row);
		new_line = term->nl_addr[row];
		if (*new_line == '\n')
			new_line++;
		if (term->nl_addr[row + 1])
			write(1, new_line, term->nl_addr[row + 1] - new_line);
		else
			write(1, new_line, &input[term->bytes] - new_line);
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
