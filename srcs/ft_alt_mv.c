/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:07:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_alt_mv_left(t_term *term, char *input)
{
	while (term->indx && ft_isspace(&input[term->indx - 1]))
		term->indx--;
	while (term->indx && !ft_isspace(&input[term->indx - 1]))
		term->indx--;
	term->c_col = &input[term->indx] - term->new_line_addr[term->c_row];
	if (!term->c_row)
		term->c_col += 3; // ft_strlen prompt
	else
		term->c_col += 2;
	ft_setcursor(term->c_col, term->c_row);
}
// static void	ft_alt_mv_left(t_term *term, char *input)
// {
// 	while (term->c_col > 0 && ft_isspace(&input[term->c_col - 1]))
// 		term->c_col--;
// 	while (term->c_col > 0 && !ft_isspace(&input[term->c_col - 1]))
// 		term->c_col--;
// 	ft_setcursor(term->c_col, term->c_row);
// }

static void	ft_alt_mv_right(t_term *term, char *input)
{
	while ((int)term->indx < term->bytes && ft_isspace(&input[term->indx]))
		term->indx++;
	while ((int)term->indx < term->bytes && !ft_isspace(&input[term->indx]))
		term->indx++;
	term->c_col = &input[term->indx] - term->new_line_addr[term->c_row];
	if (!term->c_row)
		term->c_col += 3; // ft_strlen prompt
	else
		term->c_col += 2;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_alt_mv_up(t_term *term)
{
	if (term->c_row)
		term->c_row--;
	ft_setcursor(--term->c_col, --term->c_row);
}

static void	ft_alt_mv_down(t_term *term)
{
	term->c_row++;
	ft_setcursor(--term->c_col, ++term->c_row);
}

void	ft_alt_cursor_mv(t_term *term, char *input)
{
	if (term->ch == 98 && &input[term->indx] > term->new_line_addr[term->c_row])
		ft_alt_mv_left(term, input);
	else if (term->ch == 102)
		ft_alt_mv_right(term, input);
	else if (term->ch == 49)
	{
		term->ch = ft_get_input();
		if (term->ch == 59)
		{
			term->ch = ft_get_input();
			if (term->ch == 51)
			{
				term->ch = ft_get_input();
				if (term->ch == 65 && (term->total_row > 0))
					ft_alt_mv_up(term);
				if (term->ch == 66 && (term->c_row < term->total_row))
					ft_alt_mv_down(term);
			}
		}
	}
}
