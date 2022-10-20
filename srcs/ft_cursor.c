/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:33:48 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 13:37:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_cursor_right(t_term *term)
{
	if (term->cursor)
		term->cursor++;
	write(1, "\033[1C", 4);
}

void	ft_cursor_left(t_term *term)
{
	if (term->cursor)
		term->cursor--;
	write(1, "\033[1D", 4);
}

void	ft_cursor_up(t_term *term)
{
	if (term->cur_row)
		term->cur_row--;
	write(1, "\033[1A", 4);
}

void	ft_cursor_down(t_term *term)
{
	term->cur_row++;
	write(1, "\033[1B", 4);
}

void	ft_cursor_beginning(int *cur)
{
	char	*tofree;

	tofree = NULL;
	write(1, "\033[", 2);
	tofree = ft_itoa(*cur);
	write(1, tofree, ft_intlen(*cur));
	ft_strdel(&tofree);
	write(1, "D", 1);
	cur[0] = 0;
}

void	ft_cursor_end(int *cur, int *col)
{
	char	*tofree;

	tofree = NULL;
	write(1, "\033[", 2);
	tofree = ft_itoa(*col - *cur);
	write(1, tofree, ft_intlen(*col - *cur));
	ft_strdel(&tofree);
	write(1, "C", 1);
	cur[0] = *col;
}

void	ft_cursor_mv(t_term *term)
{
	if (term->ch== LEFT && term->cursor)
		ft_cursor_left(term);
	if (term->ch== RIGHT && (term->cursor < term->col))
		ft_cursor_right(term);
	if (term->ch== DOWN && (term->cur_row < term->row))
		ft_cursor_down(term);
	if (term->ch== UP && (term->cur_row > 0))
		ft_cursor_up(term);
}
