/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:48:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_print_prompt(ssize_t row)
{
	if (!row)
		ft_putstr(PROMPT);
	else
		ft_putstr(MINI_PROMPT);
}

static void	ft_print_line_trail(t_term *t)
{
	ssize_t	row;
	char	*new_line;

	row = t->c_row;
	new_line = NULL;
	ft_run_capability("cd");
	while (row <= t->total_row)
	{
		if (row == t->c_row)
		{
			if (t->nl_addr[row + 1])
				write(1, &t->inp[t->index], (size_t)(t->nl_addr[row + 1] - &t->inp[t->index]));
			else
				write(1, &t->inp[t->index], (size_t)((&t->inp[t->bytes] - &t->inp[t->index]) + 1));	
		}
		else
		{
			ft_setcursor(0, ft_get_linenbr());
			if (ft_is_prompt_line(t, row))
				ft_print_prompt(row);
			new_line = t->nl_addr[row];
			if (t->nl_addr[row + 1])
				write(1, new_line, (size_t)(t->nl_addr[row + 1] - new_line));
			else
				write(1, new_line, (size_t)((&t->inp[t->bytes] - new_line) + 1));
		}
		row++;
	}
}

void	ft_print_trail(t_term *t)
{
	ssize_t row;

	row = ft_get_linenbr();
	ft_run_capability("vi");
	ft_print_line_trail(t);
	ft_setcursor(t->c_col, row);
	ft_run_capability("ve");
}
