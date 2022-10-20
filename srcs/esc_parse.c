/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 12:33:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	shift_arrow(int *bytes, int *cur, int *c)
{
	c[0] = get_input();
	c[0] = get_input();
	c[0] = get_input();
	if (*c == 'D' && *cur)
		ft_cursor_beginning(cur);
	if (*c == 'C' && *cur < *bytes)
		ft_cursor_end(cur, bytes);
}

void	esc_parse(char *input, t_term *term)
{
	term->ch = get_input();
	if (term->ch == '[')
	{
		term->ch = get_input();
		if (term->ch == 'D')
			term->ch = LEFT;
		if (term->ch == 'C')
			term->ch = RIGHT;
		if (term->ch == 'A')
			term->ch = UP;
		if (term->ch == 'B')
			term->ch = DOWN;
		if (term->ch == 'H' && term->cursor)
			ft_cursor_beginning(&term->cursor);
		if (term->ch == 'F' && term->cursor < term->bytes)
			ft_cursor_end(&term->cursor, &term->bytes);
		if (term->ch == '1')
			shift_arrow(&term->bytes, &term->cursor, &term->ch);
		ft_cursor_mv(term);
	}
	if (term->ch == 'b')
		alt_mv_left(&term->cursor, input);
	if (term->ch == 'f')
		alt_mv_right(&term->cursor, input, &term->bytes);
	term->ch = 0;
}
