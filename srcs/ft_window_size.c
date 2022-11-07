/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 12:44:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	set_new_cur_pos(t_term *term)
{
	while (term->nl_addr[term->c_row] && &term->inp[term->index] >= term->nl_addr[term->c_row])
		term->c_row++;
	term->c_row--;
	term->c_col = 0;
	if (is_prompt_line(term, term->c_row))
	{
		if (!term->c_row)
			term->c_col = term->prompt_len;
		else
			term->c_col = term->m_prompt_len;
	}
	term->c_col += &term->inp[term->index] - term->nl_addr[term->c_row];
	ft_setcursor(term->c_col, term->c_row);
}

void	ft_window_size(t_term *term)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	term->ws_col = size.ws_col;
	term->ws_row = size.ws_row;
	if (*term->inp)
	{
		term->quote = 0;
		term->q_qty = 0;
		reset_nl_addr(term, term->inp);
		term->c_row = 0;
		set_new_cur_pos(term);
		ft_print_trail(term, term->inp);
	}
}
