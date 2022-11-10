/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/10 11:58:40 by mbarutel         ###   ########.fr       */
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

static void	ft_print_line_trail(t_term *t)
{
	size_t	row;
	char	*new_line;

	new_line = NULL;
	row = 0;
	ft_setcursor(0, row + t->start_row);
	ft_run_capability("cd");
	while (row <= t->total_row)
	{
		if (ft_is_prompt_line(t, row))
			ft_print_prompt(row);
		new_line = t->nl_addr[row];
		if (*new_line == '\n')
			new_line++;
		if (t->nl_addr[row + 1])
			write(1, new_line, t->nl_addr[row + 1] - new_line);
		else
			write(1, new_line, &t->inp[t->bytes] - new_line);
		ft_setcursor(0, ++row + t->start_row);
	}
}

void	ft_print_trail(t_term *t)
{
	ft_run_capability("vi");
	ft_print_line_trail(t);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
	ft_run_capability("ve");
}
