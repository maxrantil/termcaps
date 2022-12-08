/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 16:26:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It sets the cursor position
 * to the position of the character at the current index
 *
 * @param t the term structure
 */
// static void	set_new_cur_pos(t_term *t)
// {
// 	while (t->nl_addr[t->c_row] \
// 	&& &t->inp[t->index] >= t->nl_addr[t->c_row])
// 		t->c_row++;
// 	t->c_row--;
// 	t->c_col = 0;
// 	if (ft_is_prompt_line(t, t->c_row))
// 	{
// 		if (!t->c_row)
// 			t->c_col = t->prompt_len;
// 		else
// 			t->c_col = t->m_prompt_len;
// 	}
// 	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
// 	ft_setcursor(t->c_col, t->c_row + t->start_row);
// }

static void	ft_print_new_inp_proto(t_term *t)
{
	int		len;

	while (t->nl_addr[t->c_row])
	{
		if (t->nl_addr[t->c_row + 1])
			len = (int)(t->nl_addr[t->c_row + 1] - t->nl_addr[t->c_row]);
		else
			len = (int)(t->inp + t->bytes - t->nl_addr[t->c_row]);
		if (ft_is_prompt_line(t, t->c_row))
		{
			if (!t->c_row)
				t->c_col = write(STDOUT_FILENO, PROMPT, t->prompt_len);
			else
				t->c_col = write(STDOUT_FILENO, MINI_PROMPT, t->m_prompt_len);
		}
		t->c_col += write(STDOUT_FILENO, t->nl_addr[t->c_row], len);
		if (!t->nl_addr[t->c_row + 1])
			break ;
		t->c_row++;	
	}
}

/*
 * It resets the cursor position and prints the trail of the input string
 *
 * @param t the term structure
 */
void	ft_window_size(t_term *t)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp)
	{
		ft_setcursor(0, t->start_row);
		ft_run_capability("cd");
		t->quote = 0;
		t->q_qty = 0;
		t->bslash = 0;
		t->heredoc = 0;
		ft_reset_nl_addr(t);
		t->c_row = 0;
		// set_new_cur_pos(t);
		ft_print_new_inp_proto(t);
	}
}
