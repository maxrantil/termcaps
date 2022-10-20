/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:15:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	shift_arrow(t_term *term)
{
	term->ch = get_input();
	term->ch = get_input();
	term->ch = get_input();
	if (term->ch == 'D' && term->indx)
		ft_cursor_beginning(term);
	if (term->ch == 'C' && term->c_col < term->indx)
		ft_cursor_end(term);
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
			ft_cursor_beginning(term);
		if (term->ch == 'F' && term->c_col < term->indx)
			ft_cursor_end(term);
		if (term->ch == '1')
			shift_arrow(term);
		ft_cursor_mv(term);
	}
	if (term->ch == 'b')
		alt_mv_left(&term->indx, input);
	if (term->ch == 'f')
		alt_mv_right(&term->indx, input, &term->c_col);
	term->ch = 0;
}
