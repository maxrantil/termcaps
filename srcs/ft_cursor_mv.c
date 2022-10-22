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

static void	ft_cursor_up(t_term *term, int his)
{
	ft_run_capability("cb");
	ft_run_capability("cl");
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - his));
}

static void	ft_cursor_down(t_term *term, int his)
{
	ft_run_capability("cb");
	ft_run_capability("cl");
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - his));
}

void	ft_cursor_mv(t_term *term)
{
	static size_t his;

	if (term->ch == 'D' && term->bytes)
		ft_cursor_left(term);
	else if (term->ch == 'C' && (term->c_col < term->bytes))
		ft_cursor_right(term);
	else if (term->ch == 'A' && his < term->v_history.len)
		ft_cursor_up(term, ++his);
	else if (term->ch == 'B' && his > 0)
		ft_cursor_down(term, --his);
}
