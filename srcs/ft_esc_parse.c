/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:52:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_beginning(t_term *term)
{
	term->c_col = 0;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_cursor_end(t_term *term)
{
	term->c_col = term->bytes;
	ft_setcursor(term->c_col, term->c_row);
}

static void	shift_arrow(t_term *term)
{
	term->ch = ft_get_input();
	term->ch = ft_get_input();
	term->ch = ft_get_input();
	if (term->ch == 'D' && term->bytes)
		ft_cursor_beginning(term);
	if (term->ch == 'C' && term->c_col < term->bytes)
		ft_cursor_end(term);
}

void	ft_esc_parse(t_term *term, char *input)
{
	term->ch = ft_get_input();
	if (term->ch == '[')
	{
		term->ch = ft_get_input();
		if (term->ch >= 'A' && term->ch <= 'D')
			ft_cursor_mv(term);
		if (term->ch == 49)
			ft_alt_cursor_mv(term, input);
		if (term->ch == 'H' && term->bytes)
			ft_cursor_beginning(term);
		if (term->ch == 'F' && term->c_col < term->bytes)
			ft_cursor_end(term);
		if (term->ch == '1')
			shift_arrow(term);
	}
	if (term->ch == 98 || term->ch == 102)
		ft_alt_cursor_mv(term, input);
	term->ch = 0;
}
