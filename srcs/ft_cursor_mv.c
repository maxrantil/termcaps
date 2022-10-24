/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_mv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/24 11:22:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_right(char *input, t_term *term)
{
	if ((int)term->indx < term->bytes && input[term->indx] != '\n')
	{
		term->indx++;
		// if (input[term->indx] == '\n' && term->c_row)
		// 	term->c_col++;
		ft_setcursor(++term->c_col, term->c_row);
	}
}

static void	ft_cursor_left(char *input, t_term *term)
{
	term->indx--;
	term->c_col--;
	if (&input[term->indx + 1] == term->new_line_addr[term->c_row])
	{
		if (term->c_row == 1)
			term->c_col = (term->new_line_addr[term->c_row] - term->new_line_addr[term->c_row - 1]) + 2;
		else
			term->c_col = (term->new_line_addr[term->c_row] - term->new_line_addr[term->c_row - 1]) + 1;
		term->c_row--;
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_cursor_up(t_term *term)
{
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - 1));
}

static void	ft_cursor_down(t_term *term)
{
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len));
}

void	ft_cursor_mv(char *input, t_term *term)
{
	if (term->ch == 'D' && term->indx)
		ft_cursor_left(input, term);
	else if (term->ch == 'C') // THis might need to change so, if term->indx == '\n', move to the next line
		ft_cursor_right(input, term);
	else if (term->ch == 'A')
		ft_cursor_up(term);
	else if (term->ch == 'B')
		ft_cursor_down(term);
}
