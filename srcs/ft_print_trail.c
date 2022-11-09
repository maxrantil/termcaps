/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 09:58:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_print_prompt(size_t row)
{
	if (!row)
		ft_putstr(PROMPT);
	else
		ft_putstr(MINI_PROMPT);
}

static void	ft_print_line_trail(t_term *term)
{
	size_t	row;
	char	*new_line;

	new_line = NULL;
	row = 0;
	ft_setcursor(0, row);
	ft_run_capability("cd");
	while (row <= term->total_row)
	{
		if (ft_is_prompt_line(term, row))
			ft_print_prompt(row);
		new_line = term->nl_addr[row];
		if (*new_line == '\n')
			new_line++;
		if (term->nl_addr[row + 1])
			write(1, new_line, term->nl_addr[row + 1] - new_line);
		else
			write(1, new_line, &term->inp[term->bytes] - new_line);
		ft_setcursor(0, ++row);
	}
}

void	ft_print_trail(t_term *term)
{
	ft_run_capability("vi");
	ft_print_line_trail(term);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
