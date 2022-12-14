/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:04:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 15:41:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

// static void	set_new_cur_pos(t_term *t)
// {
// 	while (t->nl_addr[t->c_row] \
// 	&& &t->inp[t->index] >= t->nl_addr[t->c_row])
// 		t->c_row++;
// 	t->c_row--;
// 	t->c_col = ft_get_prompt_len(t, t->c_row);
// 	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
// 	ft_setcursor(t->c_col, t->c_row);
// }

/*
 * It pastes the contents of the clipboard into the input buffer
 *
 * @param t The term structure.
 */
void	ft_paste(t_term *t)
{
	int		i;

	i = -1;
	if (t->clipboard.buff)
	{
		ft_run_capability("vi");
		while (t->bytes < BUFFSIZE && t->clipboard.buff[++i])
		{
			t->c_col++;
			ft_putc(t->clipboard.buff[i]);
			ft_shift_nl_addr(t, 1);
			if (t->inp[t->index])
				ft_shift_insert(t);
			t->inp[t->index++] = t->clipboard.buff[i];
			t->bytes++;
			ft_trigger_nl(t);
			if (t->c_col == t->ws_col)
				t->c_row++;
		}
		if (t->inp[t->index])
			ft_print_trail(t);
		if (t->clipboard.type == CUT)
			ft_strdel(&t->clipboard.buff);
		ft_run_capability("ve");
	}
}
