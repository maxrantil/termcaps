/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.cap->ch                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:23:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:38:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	delete(char *input, t_termcap *cap)
{
	deletion_shift(input, cap, DEL);
	clear_trail();
	print_trail(input, cap);
}

void	backspace(char *input, t_termcap *cap)
{
	cursor_left(cap);
	clear_trail();
	if (cap->cursor == cap->bytes)
	{
		cap->bytes--;
		cap->cursor--;
		input[cap->cursor] = '\0';
	}
	else
		deletion_shift(input, cap, BCK);
	if (input[cap->cursor])
		print_trail(input, cap);
}

void	cursor_mv(t_termcap *cap)
{
	if (cap->ch== LEFT && cap->cursor)
		cursor_left(cap);
	if (cap->ch== RIGHT && (cap->cursor < cap->bytes))
		cursor_right(cap);
	if (cap->ch== DOWN && (cap->cur_row < cap->row))
		cursor_down(cap);
	if (cap->ch== UP && (cap->cur_row > 0))
		cursor_up(cap);
}

void	char_print(char *input, t_termcap *cap)
{
	write(1, &cap->ch, 1);
	if (input[cap->cursor])
		insertion_shift(input, cap);
	input[cap->cursor++] = cap->ch;
	if (input[cap->cursor])
		print_trail(input, cap);
	cap->bytes++;
}
