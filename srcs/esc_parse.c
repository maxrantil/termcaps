/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 14:18:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	shift_arrow(int *col, int *cur, int *c)
{
	c[0] = get_input();
	c[0] = get_input();
	c[0] = get_input();
	if (*c == 'D' && *cur)
		ft_cursor_beginning(cur);
	if (*c == 'C' && *cur < *col)
		ft_cursor_end(cur, col);
}

void	esc_parse(t_term *term, char *input)
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
		if (term->ch == 'H' && term->indx)
			ft_cursor_beginning(&term->indx);
		if (term->ch == 'F' && term->indx < term->c_col)
			ft_cursor_end(&term->indx, &term->c_col);
		if (term->ch == '1')
			shift_arrow(&term->c_col, &term->indx, &term->ch);
		ft_cursor_mv(term);
	}
	if (term->ch == 'b')
		alt_mv_left(&term->indx, input);
	if (term->ch == 'f')
		alt_mv_right(&term->indx, input, &term->c_col);
	term->ch = 0;
}
