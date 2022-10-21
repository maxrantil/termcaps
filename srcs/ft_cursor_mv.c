/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_mv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/21 12:38:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_right(t_term *term)
{
	term->indx++;
	ft_setcursor(++term->c_col, term->c_row);
}

static void	ft_cursor_left(t_term *term)
{
	term->indx--;
	ft_setcursor(--term->c_col, term->c_row);
}

static void	ft_cursor_up(t_term *term)
{
	if (term->c_row)
		term->c_row--;
	ft_setcursor(--term->c_col, --term->c_row);
}

static void	ft_cursor_down(t_term *term)
{
	term->c_row++;
	ft_setcursor(--term->c_col, ++term->c_row);
}

void	ft_cursor_mv(t_term *term)
{
	if (term->ch == LEFT && term->bytes)
		ft_cursor_left(term);
	if (term->ch == RIGHT && (term->c_col < term->bytes))
		ft_cursor_right(term);
	if (term->ch == DOWN && (term->c_row < term->total_row))
		ft_cursor_down(term);
	if (term->ch == UP && (term->total_row > 0))
		ft_cursor_up(term);
}
