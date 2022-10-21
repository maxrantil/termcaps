/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_mv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/21 15:31:13 by mrantil          ###   ########.fr       */
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
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - 1));
}

static void	ft_cursor_down(t_term *term)
{
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len));
}

void	ft_cursor_mv(t_term *term)
{
	if (term->ch == 'D' && term->bytes)
		ft_cursor_left(term);
	else if (term->ch == 'C' && (term->c_col < term->bytes))
		ft_cursor_right(term);
	else if (term->ch == 'A')
		ft_cursor_up(term);
	else if (term->ch == 'B')
		ft_cursor_down(term);
}
